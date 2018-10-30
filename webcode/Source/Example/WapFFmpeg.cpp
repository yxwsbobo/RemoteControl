//
// Created by Kin on 2018-10-22.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#include "WapFFmpeg.h"

#include <iostream>

webffmpeg::WapFFmpeg::WapFFmpeg() {

    TempFrame = av_frame_alloc();
    InnerFrame = av_frame_alloc();
    InnerPackage = av_packet_alloc();

}

AVFrame * webffmpeg::WapFFmpeg::GetFrame(int* PackageInfo) {

    InnerPackage->size = PackageInfo[1];
    InnerPackage->flags = PackageInfo[2];
    InnerPackage->buf = nullptr;
    InnerPackage->data = (uint8_t*)&PackageInfo[3];

    if(avcodec_send_packet(DecoderCtx,InnerPackage ) != 0){
        std::cout<<"avcodec_send_packet Failed"<<std::endl;
        return nullptr;
    }

    if(avcodec_receive_frame(DecoderCtx,TempFrame) < 0){
        std::cout<<"receive frame failed "<<std::endl;
        return nullptr;
    }

    sws_scale( ConvertCtx, TempFrame->data, TempFrame->linesize, 0, TempFrame->height, InnerFrame->data, InnerFrame->linesize );

    return InnerFrame;
}

void webffmpeg::WapFFmpeg::Init() {

    if(DecoderCtx != nullptr)
    {
        avcodec_free_context(&DecoderCtx);
    }

    auto nDecoder = avcodec_find_decoder( AV_CODEC_ID_HEVC );
    if(!nDecoder){
        std::cout<<"Can't find Decoder"<<std::endl;
        return;
    }

    DecoderCtx = avcodec_alloc_context3( nDecoder );
    if(!DecoderCtx){
        std::cout<<"Can't alloc CodecCtx"<<std::endl;
        return;
    }

    if(avcodec_open2(DecoderCtx,nDecoder,nullptr) < 0){
        std::cout<<"avcodec open failed"<<std::endl;
        return;
    }
}

void webffmpeg::WapFFmpeg::InitScreen(int Width, int Height) {
    ScreenWidth = Width;
    ScreenHeight = Height;

    av_frame_unref(InnerFrame);

    InnerFrame->format = AV_PIX_FMT_RGBA;
    InnerFrame->width = Width;
    InnerFrame->height = Height;
    av_frame_get_buffer( InnerFrame, 32 );
}

void webffmpeg::WapFFmpeg::InitVideo(int Width, int Height) {

    if(ConvertCtx != nullptr)
    {
        sws_freeContext( ConvertCtx );
    }

    ConvertCtx = sws_getContext( Width, Height, AV_PIX_FMT_YUV420P, ScreenWidth,
                                 ScreenHeight, AV_PIX_FMT_RGBA, SWS_POINT, nullptr, nullptr, nullptr);
}

