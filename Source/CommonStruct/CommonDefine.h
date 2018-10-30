#include <utility>

//
// Created by Kin on 2018-10-11.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#ifndef KINREMOTECONTROL_COMMONDEFINE_H
#define KINREMOTECONTROL_COMMONDEFINE_H

#include <string>
#include <memory>
#include <KinBase/BetterEnum.h>

namespace websocketpp
{
template <typename T>
class server;

template <typename T>
class client;

namespace config
{
struct asio;
struct asio_client;
}
}

namespace KinRemoteControl {

BETTER_ENUM(ClientState,int,
    OffLine,
    OnLine);


struct ClientInfo
{
  enum ClientType
  {
    UnValid,
    Controlled,
    Master
  } Type;

  ClientInfo(ClientType type = UnValid, std::weak_ptr<void> hdl = std::weak_ptr<void>())
  :Type{type},Hdl{std::move(hdl)}
  {}
  std::weak_ptr<void> Hdl;
  std::string RemoteName;
};

BETTER_ENUM(RequestType, int,
            RegistControlled,
            RegistMaster,
            ControlledChanged,
            ControlledList,
            ListControlled,
            ControlMachine,
            ControlMachineResult,
            StopControl,
            ControlOrder);

BETTER_ENUM(SocketType,int,
    VideoPacket);

BETTER_ENUM(ControlType, int,
    MouseMove,
    LeftButtonDown,
    LeftButtonUp,
    RightButtonDown,
    RightButtonUp,
    MiddleButtonDown,
    MiddleButtonUp,
    MiddleButtonWheel,
    KeyboardDown,
    KeyboardUp);

}

#endif //KINREMOTECONTROL_COMMONDEFINE_H
