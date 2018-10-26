//
// Created by Kin on 2018-10-11.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#include "../Client/RCClient.h"
#include <thread>
#include <future>
#include <iostream>

int main()
{
    using namespace KinRemoteControl;

    RCClient Client;
    auto ft = std::async([&]{
        Client.Connect("192.168.7.189",5656);
    });


    std::string Cmd;

    while(std::getline(std::cin,Cmd))
    {
        if(Cmd == "q")
        {
            break;
        }
        if(Cmd == "t")
        {
            Client.TestFun();
        }
    }

    return 0;
}