include(KinCommonFunction)

find_package(KinBase)
find_package(KinBoost)
find_package(websocketpp)

set(KinAllLibs Mswsock Ws2_32 libboost_system-mgw81-mt-x64-1_68 ${KinAllLibs} )

KinAddFindModule(KinRemoteControl)
