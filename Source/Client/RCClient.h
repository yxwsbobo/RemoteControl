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
#include <atomic>
extern "C"{
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
#include <libavutil/audio_fifo.h>
}

namespace KinRemoteControl {

/**
 * @brief
 * @date 2018-10-11
 * @author Kin
 * @copyright Copyright © 2018 jihuisoft. All rights reserved.
 */
    class RCClient {
    public:
        RCClient() ;

        ~RCClient() = default;

        void Connect(const std::string& Uri, uint16_t Port);

        void TestFun();

     private:
      void OnConnected(std::weak_ptr<void> hdl);
      void OnClosed(std::weak_ptr<void> hdl);
      void OnReceive(std::weak_ptr<void> hdl, const std::string& Msg);
      void OnReceiveBinary(std::weak_ptr<void> hdl, const std::string& Msg);

     private:
        void OnControlOrder(const nlohmann::json& data);

        void GetAndSendVideo(int Width, int Height);

        void OnStopControl();

     private:
      using CoreType = websocketpp::client<websocketpp::config::asio_client>;

        SystemControl::KinControl SysControl;
        std::shared_ptr<CoreType> Core;
        std::weak_ptr<void> RemoteHdl;

        AVFormatContext* ScreenCtx = nullptr;
        std::atomic_bool Running = false;

        int* TempBuffer = nullptr;
        AVPacket *InnerPkg = nullptr;
        AVFrame *InnerFrame = nullptr;
    };

}
#endif //KINREMOTECONTROL_RCCLIENT_H
