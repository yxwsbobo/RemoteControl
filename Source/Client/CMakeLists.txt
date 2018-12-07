cmake_minimum_required(VERSION 3.12)



project(Client)

set(CMAKE_CXX_STANDARD 17)

find_package(SystemControl)
find_package(nlohmann)
find_package(KinBoost)
find_package(websocketpp)

add_library(Client RCClient.cpp RCClient.h)

target_link_libraries(Client libavcodec.dll.a libavdevice.dll.a libavfilter.dll.a libavformat.dll.a libavutil.dll.a libpostproc.dll.a libswresample.dll.a libswscale.dll.a ${KinAllLibs})