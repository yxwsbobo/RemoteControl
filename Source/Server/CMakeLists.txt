cmake_minimum_required(VERSION 3.12)

project(Server)

set(CMAKE_CXX_STANDARD 17)

find_package(KinBoost)
find_package(websocketpp)
find_package(nlohmann)

add_library(Server RCServer.cpp RCServer.h)

target_link_libraries(Server ${KinAllLibs})