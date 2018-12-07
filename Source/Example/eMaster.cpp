//
// Created by Kin on 2018-10-31.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#include <string>
#include <iostream>

#include "../RCMaster/RCMaster.h"

int main()
{
    KinRemoteControl::RCMaster Master;

    Master.ConnectTo("ws://192.168.7.189");

    Master.Run();

    std::string Cmd;
    while(std::cin>>Cmd)
    {
        if(Cmd == "q")
        {
            break;
        }
    }
}