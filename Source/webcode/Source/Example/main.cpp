//
// Created by Kin on 2018-10-22.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#include "JsFunctions.h"
#include "WapFFmpeg.h"
#include "WapSdl.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
#include <emscripten.h>

webffmpeg::WapFFmpeg *wapFFmpeg;
webffmpeg::WapSdl *wapSdl;

int * VideoBuffer;

enum class SocketType
{
    VideoPacket
};

extern  "C" {

    static int Num = 0;

    EMSCRIPTEN_KEEPALIVE void SocketMessage( int *Buffer, int Size) {

        if(Buffer[0] == (char)SocketType::VideoPacket)
        {
            auto Frame = wapFFmpeg->GetFrame(Buffer);
            wapSdl->DisplayFrame(Frame->data[0],Frame->linesize[0]);
        }
        else
        {
            std::cout<<"not show :"<<Buffer[0]<<std::endl;
        }
    }

    EMSCRIPTEN_KEEPALIVE void InitPlayer(){
        wapFFmpeg->Init();
    }

    EMSCRIPTEN_KEEPALIVE void InitScreen(int w, int h){
        wapSdl->InitScreen(w,h);
        wapFFmpeg->InitScreen(w,h);
    }

    EMSCRIPTEN_KEEPALIVE void InitVideo(int w, int h){
        wapFFmpeg->InitVideo(w,h);
    }

    EMSCRIPTEN_KEEPALIVE int* GetVideoBuffer(){
        return VideoBuffer;
    }

    EMSCRIPTEN_KEEPALIVE void OnSocketConnected(){
    }

    EMSCRIPTEN_KEEPALIVE void OnSocketClosed(){
    }
    int av_get_cpu_flags()
    {
        return 0;
    }



}

void ReferenceFunctionName()
{
    IsConnected();
    IsControlling();
//    RefreshControlledList();

}

int main()
{

    VideoBuffer = (int*)new char[1024*1024];
    if(VideoBuffer == nullptr)
    {
        ReferenceFunctionName();
    }

    wapFFmpeg = new webffmpeg::WapFFmpeg;
    wapSdl = new webffmpeg::WapSdl;

//    InitInnerScriptInterface();

    SocketConnect();
    InitPlayer();
    InitScreen(1280,720);
    InitVideo(1280,720);
    return 0;
}