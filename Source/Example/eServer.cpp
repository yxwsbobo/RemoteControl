//
// Created by Kin on 2018-10-11.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#include "../Server/RCServer.h"
#include <iostream>

int main()
{
    using namespace KinRemoteControl;
    RCServer server;
    server.Run();

    std::cout<<"over"<<std::endl;

    std::string quite;
    std::cin>>quite;

    return 0;
}