cmake_minimum_required(VERSION 3.12)
project(KinRemoteControl)

set(CMAKE_CXX_STANDARD 17)

find_path(KinFrameworkPath KinCommonSetting.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${KinFrameworkPath})
include(KinCommonSetting)

find_package(KinBase)

link_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(KinAllLibs Mswsock Ws2_32 libboost_system-mgw81-mt-x64-1_68 ${KinAllLibs} )

add_subdirectory(Source)