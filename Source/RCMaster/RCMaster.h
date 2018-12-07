//
// Created by Kin on 2018-10-24.
// Copyright © 2018 jihuisoft. All rights reserved.
//

#ifndef KINREMOTECONTROL_RCMASTER_H
#define KINREMOTECONTROL_RCMASTER_H

#include <string>

namespace KinRemoteControl {

/**
 * @brief
 * @date 2018-10-24
 * @author Kin
 * @copyright Copyright © 2018 jihuisoft. All rights reserved.
 */
class RCMaster
{
 public:
    explicit RCMaster();
    ~RCMaster() = default;

    void ConnectTo(std::string Url);

    void Run(int NumberOfThreads = 2);

 private:

};

}
#endif //KINREMOTECONTROL_RCMASTER_H
