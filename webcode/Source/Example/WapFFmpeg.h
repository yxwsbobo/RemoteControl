//
// Created by Kin on 2018-10-22.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#ifndef WEBFFMPEG_WAPFFMPEG_H
#define WEBFFMPEG_WAPFFMPEG_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

#include <string>
namespace webffmpeg {

/**
 * @brief
 * @date 2018-10-22
 * @author Kin
 * @copyright Copyright © 2018 jihuisoft. All rights reserved.
 */
class WapFFmpeg
{
 public:
    WapFFmpeg();
    ~WapFFmpeg() = default;
    void Init();
    void InitScreen(int Width, int Height);
    void InitVideo(int Width, int Height);
    AVFrame * GetFrame(int* PackageInfo);


 private:
    AVCodecContext * DecoderCtx = nullptr;
    AVFrame * InnerFrame = nullptr;
    AVFrame * TempFrame = nullptr;
    AVPacket *InnerPackage = nullptr;
    SwsContext * ConvertCtx = nullptr;

    int ScreenWidth = 0;
    int ScreenHeight = 0;
};

}
#endif //WEBFFMPEG_WAPFFMPEG_H
