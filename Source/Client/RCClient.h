//
// Created by Kin on 2018-10-11.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#ifndef KINREMOTECONTROL_RCCLIENT_H
#define KINREMOTECONTROL_RCCLIENT_H

#include <string>
#include <memory>
#include "../CommonStruct/CommonDefine.h"
#include <SystemControl/KinControl.h>
#include <nlohmann/json_fwd.hpp>

namespace KinRemoteControl {

/**
 * @brief
 * @date 2018-10-11
 * @author Kin
 * @copyright Copyright © 2018 jihuisoft. All rights reserved.
 */
    class RCClient {
    public:
        RCClient() = default;

        ~RCClient() = default;

        void Connect(const std::string& Uri, uint16_t Port);

     private:
      void OnConnected(std::weak_ptr<void> hdl);
      void OnClosed(std::weak_ptr<void> hdl);
      void OnReceive(std::weak_ptr<void> hdl, const std::string& Msg);
      void OnReceiveBinary(std::weak_ptr<void> hdl, const std::string& Msg);

     private:
        void OnControlOrder(const nlohmann::json& data);

     private:
      using CoreType = websocketpp::client<websocketpp::config::asio_client>;

        SystemControl::KinControl SysControl;
        std::shared_ptr<CoreType> Core;
    };

}
#endif //KINREMOTECONTROL_RCCLIENT_H
