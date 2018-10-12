//
// Created by Kin on 2018-10-11.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#include "../Client/RCClient.h"

int main()
{
    using namespace KinRemoteControl;

    RCClient Client;
    Client.Connect("192.168.7.189",5656);

    return 0;
}