//
// Created by Kin on 2018-10-22.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#include "WapSdl.h"
#include <emscripten.h>
#include <iostream>

webffmpeg::WapSdl::WapSdl() {

    if(SDL_Init(SDL_INIT_VIDEO)){
        std::cout<<"Init SDL Failed"<<std::endl;
    }
}

void webffmpeg::WapSdl::InitScreen(int w, int h) {

    if(Window == nullptr)
    {
        Window = SDL_CreateWindow("MyWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            w, h, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
        if(Window == nullptr){
            std::cout <<" Create Window Failed"<<std::endl;
        }
    }
    else
    {
        SDL_SetWindowSize(Window,w,h);
    }

    if(Renderer != nullptr)
    {
        SDL_DestroyRenderer(Renderer);
        Renderer = nullptr;
    }

    if (Texture != nullptr)
    {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(Renderer == nullptr){
        std::cout<<"Create Render Failed"<<std::endl;
    }

    Texture =  SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STREAMING, w, h);
    if(Texture == nullptr){
        std::cout<<"SDL_CreateTexture Failed"<<std::endl;
    }

    SDL_SetRenderDrawColor(Renderer, 180, 180, 180, 255);
    SDL_RenderClear(Renderer);
    SDL_RenderPresent(Renderer);

}
void webffmpeg::WapSdl::DisplayFrame(void *Pixels, int Pitch) {
    SDL_UpdateTexture(Texture, nullptr, Pixels, Pitch);
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, Texture, nullptr, nullptr);
    SDL_RenderPresent(Renderer);
}
