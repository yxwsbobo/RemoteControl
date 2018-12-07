//
// Created by Kin on 2018-10-22.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#ifndef WEBFFMPEG_WAPSDL_H
#define WEBFFMPEG_WAPSDL_H


#include <SDL2/SDL.h>

namespace webffmpeg {

/**
 * @brief
 * @date 2018-10-22
 * @author Kin
 * @copyright Copyright © 2018 jihuisoft. All rights reserved.
 */
class WapSdl
{
 public:
    WapSdl();
    ~WapSdl() = default;

    void InitScreen(int w, int h);

    void DisplayFrame(void * Pixels, int Pitch);

 private:
    SDL_Window * Window;
    SDL_Renderer * Renderer;
    SDL_Texture* Texture;

};

}
#endif //WEBFFMPEG_WAPSDL_H
