//
// Created by Kin on 2018-10-27.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#ifndef WEBFFMPEG_JSFUNCTIONS_H
#define WEBFFMPEG_JSFUNCTIONS_H

extern  "C" {
    void SocketConnect();
//    void InitInnerScriptInterface();
//    void RefreshControlledList();
    bool IsControlling();
    bool IsConnected();
};

#endif //WEBFFMPEG_JSFUNCTIONS_H
