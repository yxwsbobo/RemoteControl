//
// Created by Kin on 2018-10-11.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#ifndef KINREMOTECONTROL_RCSERVER_H
#define KINREMOTECONTROL_RCSERVER_H

#include <memory>
#include <unordered_map>
#include "../CommonStruct/CommonDefine.h"


namespace KinRemoteControl {

/**
 * @brief
 * @date 2018-10-11
 * @author Kin
 * @copyright Copyright © 2018 jihuisoft. All rights reserved.
 */
    class RCServer {
    public:
        RCServer() = default;
        ~RCServer() = default;

        void Run(uint16_t Port = 5656);

    private:
        void OnConnected(std::weak_ptr<void> hdl);
        void OnClosed(std::weak_ptr<void> hdl);
        void OnReceive(std::weak_ptr<void> hdl, const std::string& Msg);
        void OnReceiveBinary(std::weak_ptr<void> hdl, const std::string& Msg);

    private:
        void NoticeControlledChanged(const std::string& Name,ClientState State);
        void SendControlledList(std::weak_ptr<void> hdl);

    private:
        using CoreType = websocketpp::server<websocketpp::config::asio>;

        //考虑使用带锁或无锁HashMap
        std::unordered_map<std::string,ClientInfo> ControlledClients;
        std::unordered_map<std::string,ClientInfo> MasterClients;

        std::shared_ptr<CoreType> Core;
    };

}
#endif //KINREMOTECONTROL_RCSERVER_H
