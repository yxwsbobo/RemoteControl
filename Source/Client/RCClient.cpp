#include <utility>

//
// Created by Kin on 2018-10-11.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#include "RCClient.h"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json.hpp>

#define kWarn(a, b, ...) std::cout<<b<<std::endl;
#define kInfo(a, b, ...) std::cout<<b<<std::endl;
#define kTrace(...)

void KinRemoteControl::RCClient::Connect(const std::string &Uri, uint16_t Port) {
    using MessageType = websocketpp::config::asio_client::message_type::ptr;
    Core = std::make_shared<CoreType>();

    try
    {
//  Core->set_access_channels(websocketpp::log::alevel::all);
        Core->clear_access_channels(websocketpp::log::alevel::all);
//  Core->clear_error_channels(websocketpp::log::alevel::all);

        Core->init_asio();

        Core->set_open_handler([this](std::weak_ptr<void> hdl) {
            return this->OnConnected(hdl);
        });

        Core->set_message_handler([this](std::weak_ptr<void> hdl, MessageType Msg) {
            if(Msg->get_opcode() == websocketpp::frame::opcode::value::text)
            {
                return this->OnReceive(hdl, Msg->get_payload());
            }
            else if(Msg->get_opcode() == websocketpp::frame::opcode::value::binary)
            {
                return this->OnReceiveBinary(hdl, Msg->get_raw_payload());
            }
        });

        Core->set_close_handler([this](std::weak_ptr<void> hdl) {
            return this->OnClosed(hdl);
        });

        auto uri = "ws://" + Uri + ":" + std::to_string(Port);
        websocketpp::lib::error_code ec;
        CoreType::connection_ptr con = Core->get_connection(uri, ec);

        Core->connect(con);

        Core->run();
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
void KinRemoteControl::RCClient::OnConnected(std::weak_ptr<void> hdl) {
    nlohmann::json Msg;
    Msg["type"] = (+RequestType::RegistControlled)._to_string();

    Core->send(std::move(hdl), Msg.dump(), websocketpp::frame::opcode::value::text);
}
void KinRemoteControl::RCClient::OnClosed(std::weak_ptr<void> hdl) {

}
void KinRemoteControl::RCClient::OnReceive(std::weak_ptr<void> hdl, const std::string &Msg) {
    auto Message = nlohmann::json::parse(Msg);

    try
    {
        std::string tempType = Message["type"];
        auto requestType = RequestType::_from_string(tempType.c_str());

        if (requestType == +RequestType::ControlOrder)
        {
            OnControlOrder(Message["data"]);
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
void KinRemoteControl::RCClient::OnReceiveBinary(std::weak_ptr<void> hdl, const std::string &Msg) {

}
void KinRemoteControl::RCClient::OnControlOrder(const nlohmann::json &data) {
    std::string tempType = data["type"];
    auto orderType = ControlType::_from_string(tempType.c_str());

    using namespace SystemControl;
    if(orderType == +ControlType::MouseMove)
    {
        MouseStructInfo ms;
        ms.Type = InputStructType::MouseMove;
        ms.x = data["x"];
        ms.y = data["y"];

        SysControl.MouseEvent(ms);
    }
    else if(orderType == +ControlType::LeftButtonDown)
    {
        MouseStructInfo ms;
        ms.Type = InputStructType::LeftButtonDown;
        ms.x = data["x"];
        ms.y = data["y"];

        SysControl.MouseEvent(ms);
    }
    else if(orderType == +ControlType::LeftButtonUp)
    {
        MouseStructInfo ms;
        ms.Type = InputStructType::LeftButtonUp;
        ms.x = data["x"];
        ms.y = data["y"];

        SysControl.MouseEvent(ms);
    }
    else if(orderType == +ControlType::RightButtonDown)
    {
        MouseStructInfo ms;
        ms.Type = InputStructType::RightButtonDown;
        ms.x = data["x"];
        ms.y = data["y"];

        SysControl.MouseEvent(ms);
    }
    else if(orderType == +ControlType::RightButtonUp)
    {
        MouseStructInfo ms;
        ms.Type = InputStructType::RightButtonUp;
        ms.x = data["x"];
        ms.y = data["y"];

        SysControl.MouseEvent(ms);
    }
    else if(orderType == +ControlType::MiddleButtonDown)
    {
        MouseStructInfo ms;
        ms.Type = InputStructType::MiddleButtonDown;
        ms.x = data["x"];
        ms.y = data["y"];

        SysControl.MouseEvent(ms);
    }
    else if(orderType == +ControlType::MiddleButtonUp)
    {
        MouseStructInfo ms;
        ms.Type = InputStructType::MiddleButtonUp;
        ms.x = data["x"];
        ms.y = data["y"];

        SysControl.MouseEvent(ms);
    }
    else if(orderType == +ControlType::KeyboardDown)
    {
        KeyboardStructInfo ks;
        ks.Type = InputStructType::KeyboardDown;
        ks.vkCode = data["key"];
        SysControl.KeyboardEvent(ks);
    }
    else if(orderType == +ControlType::KeyboardUp)
    {
        KeyboardStructInfo ks;
        ks.Type = InputStructType::KeyboardUp;
        ks.vkCode = data["key"];
        SysControl.KeyboardEvent(ks);
    }
}
