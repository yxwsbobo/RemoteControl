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

KinRemoteControl::RCClient::RCClient() {
    avdevice_register_all();

    InnerPkg = av_packet_alloc();
    InnerFrame = av_frame_alloc();
    TempBuffer = (int *) new char[1024*1024];
}


void KinRemoteControl::RCClient::Connect(const std::string &Uri, uint16_t Port) {
    using MessageType = websocketpp::config::asio_client::message_type::ptr;
    Core = std::make_shared<CoreType>();

    try
    {
//  Core->set_access_channels(websocketpp::log::alevel::all);
        Core->clear_access_channels(websocketpp::log::alevel::all);
//        Core->clear_error_channels(websocketpp::log::alevel::all);

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

        for (int i = 0; i != 3; ++i)
        {
            std::thread([=]{Core->run();}).detach();
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
void KinRemoteControl::RCClient::OnConnected(std::weak_ptr<void> hdl) {
    nlohmann::json Msg;
    Msg["type"] = (+RequestType::RegistControlled)._to_string();

    RemoteHdl = hdl;
    Core->send(std::move(hdl), Msg.dump(), websocketpp::frame::opcode::value::text);
}
void KinRemoteControl::RCClient::OnClosed(std::weak_ptr<void> hdl) {
    StopRecorde();
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
        else if(requestType == +RequestType::ControlMachine)
        {
            int width = Message["data"]["width"];
            int height = Message["data"]["height"];
            int bitRate = Message["data"]["bitRate"];
            int frameRate = Message["data"]["frameRate"];
            std::thread(&RCClient::GetAndSendVideo,this,width,height,bitRate,frameRate).detach();
        }
        else if(requestType == +RequestType::StopControl)
        {
            OnStopControl();
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

void KinRemoteControl::RCClient::StopRecorde() {
    Running = false;

    while(RunningThread)
    {
        std::this_thread::yield();
    }
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
    else if(orderType == +ControlType::MiddleButtonWheel)
    {
        MouseStructInfo ms;
        ms.Type = InputStructType::MiddleButtonWheel;
        ms.x = data["x"];
        ms.y = data["y"];
        ms.Info = data["info"];

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


void KinRemoteControl::RCClient::TestFun() {

//    Core->send(RemoteHdl,&mt,sizeof(mt), websocketpp::frame::opcode::value::binary);
}

AVCodecContext * GetEncodeCtx(int Width, int Height, int64_t BitRate){
    auto Encoder = avcodec_find_encoder(AV_CODEC_ID_HEVC);
    if(!Encoder)
    {
        std::cout << "Can't find Encoder" << std::endl;
        return nullptr;
    }
    auto enCtx = avcodec_alloc_context3(Encoder);
    if(!enCtx)
    {
        std::cout << "Can't alloc encoder CodecCtx" << std::endl;
        return nullptr;
    }

    enCtx->time_base = (AVRational) {1, 20};
    enCtx->width = Width;
    enCtx->height = Height;


    enCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    enCtx->bit_rate = BitRate;
    enCtx->bit_rate_tolerance = (int) (enCtx->bit_rate / 2);

    av_opt_set(enCtx->priv_data, "preset", "ultrafast", 0);
    av_opt_set(enCtx->priv_data, "tune", "zerolatency", 0);

    if(avcodec_open2(enCtx, Encoder, nullptr) < 0)
    {
        std::cout << "avcodec open failed " << std::endl;
        return nullptr;
    }
    return enCtx;
}

void KinRemoteControl::RCClient::GetAndSendVideo(int Width, int Height, int BitRate, int FrameRate) {

    StopRecorde();
    RunningTC rTC(RunningThread);

    Running = true;

    //init input Context
    if(ScreenCtx != nullptr)
    {
        avformat_close_input( &ScreenCtx );
        ScreenCtx = nullptr;
    }

    auto format = av_find_input_format( "gdigrab" );
    if(!format){
        std::cout<<"av_find_input_format failed"<<std::endl;
        return;
    }

    AVDictionary* options = nullptr;

    av_dict_set( &options, "draw_mouse", "1", 0 );
    std::string fRate = std::to_string(FrameRate);
    av_dict_set( &options, "framerate", fRate.c_str(), 0 );

    avformat_open_input(&ScreenCtx, "desktop", format, &options);

    av_dict_free( &options );
    if(avformat_find_stream_info( ScreenCtx, nullptr ) < 0){
        std::cout<<"avformat_find_stream_info failed"<<std::endl;
        return;
    }

    //Find Video CodePara
    AVCodecParameters * ScreenCodepar = nullptr;
    for( unsigned int i = 0; i < ScreenCtx->nb_streams; i++ )
    {
        if( ScreenCtx->streams[ i ]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO )
        {
            ScreenCodepar = ScreenCtx->streams[ i ]->codecpar;
        }
    }

    if(ScreenCodepar == nullptr){
        std::cout<<"Find VideoIndex Failed"<<std::endl;
        return;
    }

    //Init Decode Context
    auto Decoder = avcodec_find_decoder( ScreenCodepar->codec_id );
    if(!Decoder){
        std::cout<<"Can't find Decoder"<<std::endl;
        return;
    }
    auto DecodeCtx = avcodec_alloc_context3( Decoder );
    if(!DecodeCtx){
        std::cout<<"Can't alloc CodecCtx"<<std::endl;
        return;
    }

    if(avcodec_open2(DecodeCtx,Decoder,nullptr) < 0){
        std::cout<<"avcodec open failed"<<std::endl;
        return;
    }

    //Init Encode Context
    auto EncodeCtx = GetEncodeCtx(Width, Height, BitRate);
    if(EncodeCtx == nullptr){
        std::cout<<"GetEncodeCtx Failed"<<std::endl;
        return;
    }

    //Init Convert Context
    AVPixelFormat cvtFmt = AV_PIX_FMT_YUV420P;

    auto swsCtx = sws_getContext(ScreenCodepar->width, ScreenCodepar->height, (AVPixelFormat)ScreenCodepar->format,
        Width, Height, cvtFmt, SWS_FAST_BILINEAR, nullptr, nullptr, nullptr);
    if(!swsCtx)
    {
        std::cout << "create swsCtx Failed" << std::endl;
        return;
    }

    //Init Some Value
    auto ResultFrame = av_frame_alloc();

    ResultFrame->format = cvtFmt;
    ResultFrame->width = Width;
    ResultFrame->height = Height;
    av_frame_get_buffer(ResultFrame, 32);

    auto pkgSize = av_image_get_buffer_size(cvtFmt, Width, Height, 32);
    auto Packet = av_packet_alloc();
    av_new_packet(Packet, pkgSize);

    while(Running)
    {

        av_packet_unref(InnerPkg);

        av_read_frame(ScreenCtx, InnerPkg);

        if(avcodec_send_packet(DecodeCtx, InnerPkg) != 0)
        {
            std::cout << "avcodec_send_packet Failed" << std::endl;
        }

        av_frame_unref(InnerFrame);

        if(avcodec_receive_frame(DecodeCtx, InnerFrame) != 0)
        {
            std::cout << "receive frame failed" << std::endl;
            return;
        }

        sws_scale(swsCtx, InnerFrame->data, InnerFrame->linesize, 0, InnerFrame->height, ResultFrame->data, ResultFrame->linesize);

        if(avcodec_send_frame(EncodeCtx, ResultFrame) != 0)
        {
            std::cout << "Send frame failed" << std::endl;
            return;
        }

        if(avcodec_receive_packet(EncodeCtx, Packet) != 0)
        {
            std::cout << "receive pakage failed" << std::endl;
            return;
        }

        auto DataSize = Packet->buf->size + 20;

        TempBuffer[0] = (int) SocketType::VideoPacket;
        TempBuffer[1] = Packet->size;
        TempBuffer[2] = Packet->flags;
        memcpy(&TempBuffer[3], Packet->data, Packet->size);

        Core->send(RemoteHdl, TempBuffer, DataSize, websocketpp::frame::opcode::value::binary);
    }

    if(ScreenCtx != nullptr)
    {
        avformat_close_input( &ScreenCtx );
        ScreenCtx = nullptr;
    }

    avcodec_free_context(&DecodeCtx);
    DecodeCtx = nullptr;

    avcodec_free_context(&EncodeCtx);
    EncodeCtx = nullptr;

    sws_freeContext(swsCtx);
    swsCtx = nullptr;

    av_frame_unref( ResultFrame );
    av_frame_free( &ResultFrame );

    av_packet_unref( Packet );
    av_packet_free( &Packet );

}
void KinRemoteControl::RCClient::OnStopControl() {
    Running = false;
}
