#include <utility>

#include <utility>

#include <utility>

//
// Created by Kin on 2018-10-11.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#include "RCServer.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <functional>
#include <nlohmann/json.hpp>
#include <fmt/fmt.h>

#define kWarn(a, b, ...) std::cout<<b<<std::endl;
#define kInfo(a, b, ...) std::cout<<b<<std::endl;
#define kTrace(...)

void KinRemoteControl::RCServer::Run(uint16_t Port) {
    using MessageType = KinRemoteControl::RCServer::CoreType::message_ptr;
    try
    {
        Core = std::make_shared<CoreType>();
        Core->set_error_channels(websocketpp::log::alevel::all);
//        Core->set_access_channels(websocketpp::log::alevel::all);
        Core->clear_access_channels(websocketpp::log::alevel::all);

//    Core->clear_error_channels(websocketpp::log::alevel::all);

        Core->init_asio();

        Core->start_perpetual();


        Core->set_open_handler([this](std::weak_ptr<void> hdl) {
          return this->OnConnected(hdl);
        });

        Core->set_message_handler([this](std::weak_ptr<void> hdl, MessageType Msg) {
          if (Msg->get_opcode() == websocketpp::frame::opcode::value::text)
          {
              return this->OnReceive(hdl, Msg->get_payload());
          }
          else if (Msg->get_opcode() == websocketpp::frame::opcode::value::binary)
          {
              return this->OnReceiveBinary(hdl, Msg->get_raw_payload());
          }
        });

        Core->set_close_handler([this](std::weak_ptr<void> hdl) {
          return this->OnClosed(hdl);
        });

        Core->set_fail_handler([](std::weak_ptr<void> hdl){
            std::cout<<"Some Socket Failed"<<std::endl;
        });

        Core->listen(Port);

        // Start the server accept loop
        Core->start_accept();

        while(Running)
        {
            try
            {
                Core->run();
            }
            catch (...)
            {
                std::cout<<"Run Fail, restart"<<std::endl;
            }
        }

    }
    catch (websocketpp::exception const &e)
    {
        kWarn(lg::Logger, "WebSocket Server run Fail. what():{}", e.what());
    }
    catch (...)
    {
        kWarn(lg::Logger, "WebSocket Server run Unknown Error.");
    }

}

void KinRemoteControl::RCServer::OnConnected(std::weak_ptr<void> hdl) {
    auto con = Core->get_con_from_hdl(std::move(hdl));
    std::cout << "Connected Client :" << con->get_remote_endpoint() << std::endl;
}

void KinRemoteControl::RCServer::OnClosed(std::weak_ptr<void> hdl) {
    auto con = Core->get_con_from_hdl(std::move(hdl));

    auto endPoint = con->get_remote_endpoint();
    auto Iterator = ControlledClients.find(endPoint);
    if (Iterator != ControlledClients.end())
    {
        NoticeControlledChanged(endPoint, ClientState::OffLine);
        ControlledClients.erase(Iterator);
        return;
    }

    Iterator = MasterClients.find(endPoint);
    if (Iterator != MasterClients.end())
    {
        auto controlled = ControlledClients.find(Iterator->second.RemoteName);
        if (controlled == ControlledClients.end())
        {
            return;
        }
        nlohmann::json Result;
        Result["type"] = (+RequestType::StopControl)._to_string();

        Core->send(controlled->second.Hdl,Result.dump(),websocketpp::frame::opcode::value::text);

        MasterClients.erase(Iterator);
    }
}

void KinRemoteControl::RCServer::OnReceive(std::weak_ptr<void> hdl, const std::string &Msg) {
    auto con = Core->get_con_from_hdl(hdl);
    try
    {
        auto Message = nlohmann::json::parse(Msg);


        std::string tempType = Message["type"];
        auto requestType = RequestType::_from_string(tempType.c_str());

        if(requestType != +RequestType::ControlOrder)
        {
            std::cout<<"Receive :"<<Msg<<std::endl;
        }

        if (requestType == +RequestType::RegistControlled)
        {
            ClientInfo clientInfo{ClientInfo::Controlled, hdl};

            auto endPoint = con->get_remote_endpoint();
            ControlledClients[endPoint] = clientInfo;
            NoticeControlledChanged(endPoint, ClientState::OnLine);
        }
        else if (requestType == +RequestType::RegistMaster)
        {
            ClientInfo clientInfo{ClientInfo::Master, hdl};
            MasterClients[con->get_remote_endpoint()] = clientInfo;
        }
        else if (requestType == +RequestType::ListControlled)
        {
            SendControlledList(hdl);
        }
        else if (requestType == +RequestType::ControlMachine)
        {
            auto mName = con->get_remote_endpoint();
            auto master = MasterClients.find(mName);
            nlohmann::json Result;
            Result["type"] = (+RequestType::ControlMachineResult)._to_string();
            Result["data"]["success"] = 0;

            if (master == MasterClients.end())
            {
                Core->send(hdl, Result.dump(), websocketpp::frame::opcode::value::text);
                return;
            }

            std::string cName = Message["data"]["name"];
            auto controlled = ControlledClients.find(cName);
            if (controlled == ControlledClients.end())
            {
                Core->send(hdl, Result.dump(), websocketpp::frame::opcode::value::text);
                return;
            }

            master->second.RemoteName = cName;
            controlled->second.RemoteName = mName;

            Result["data"]["success"] = 1;
            Core->send(hdl, Result.dump(), websocketpp::frame::opcode::value::text);
            Core->send(controlled->second.Hdl,Msg,websocketpp::frame::opcode::value::text);
        }
        else if( requestType == +RequestType::StopControl)
        {
            auto mName = con->get_remote_endpoint();
            auto master = MasterClients.find(mName);

            if (master == MasterClients.end())
            {
                return;
            }

            auto controlled = ControlledClients.find(master->second.RemoteName);
            if (controlled == ControlledClients.end())
            {
                return;
            }

            master->second.RemoteName.clear();
            controlled->second.RemoteName.clear();

            Core->send(controlled->second.Hdl,Msg,websocketpp::frame::opcode::value::text);
        }
        else if (requestType == +RequestType::ControlOrder)
        {
            auto endPoint = con->get_remote_endpoint();
            auto RemoteMachine = MasterClients[endPoint].RemoteName;
            auto Remote = ControlledClients.find(RemoteMachine);
            if(Remote != ControlledClients.end())
            {
                Core->send(Remote->second.Hdl,Msg,websocketpp::frame::opcode::value::text);
            }
        }
    }
    catch (const std::exception &e)
    {
        kWarn(lg::Logger, "Parse Message Fail. what():{}", e.what());
    }
    catch (...)
    {
        kWarn(lg::Logger, "Parse Message Unknown Error.");
    }

}


void KinRemoteControl::RCServer::OnReceiveBinary(std::weak_ptr<void> hdl, const std::string &Msg) {
    auto con = Core->get_con_from_hdl(std::move(hdl));

    auto type = SocketType::_from_integral(Msg[0]);
    if(type == +SocketType::VideoPacket)
    {
        auto cClient = ControlledClients.find(con->get_remote_endpoint());

        if(cClient == ControlledClients.end())
        {
            std::cout<<"Can't find Controlled from ControlledClients"<<std::endl;
            return ;
        }

        auto rClient = MasterClients.find(cClient->second.RemoteName);
        if(rClient == MasterClients.end())
        {
            std::cout<<"Can't find Master from RemoteName "<<std::endl;
            return ;
        }
        Core->send(rClient->second.Hdl,Msg,websocketpp::frame::opcode::value::binary);
    }

}

void KinRemoteControl::RCServer::NoticeControlledChanged(const std::string &Name, ClientState State) {
    std::cout << "Change name :" << Name << std::endl;
    for (const auto&[master, info] : MasterClients)
    {
        nlohmann::json Msg;
        Msg["type"] = (+RequestType::ControlledChanged)._to_string();
        Msg["data"]["name"] = Name;
        Msg["data"]["state"] = State._to_integral();

        Core->send(info.Hdl, Msg.dump(), websocketpp::frame::opcode::value::text);
    }
}
void KinRemoteControl::RCServer::SendControlledList(std::weak_ptr<void> hdl) {
    nlohmann::json Msg;
    Msg["type"] = (+RequestType::ControlledList)._to_string();

    nlohmann::json List = nlohmann::json::array();
    for (const auto&[controlled, Info] : ControlledClients)
    {
        nlohmann::json Item;
        Item["name"] = controlled;
        List.push_back(Item);
    }

    Msg["data"] = List;

    Core->send(std::move(hdl), Msg.dump(), websocketpp::frame::opcode::value::text);
}


