cmake_minimum_required(VERSION 3.12)

project(Client)

set(CMAKE_CXX_STANDARD 17)

add_library(Client RCClient.cpp RCClient.h)

target_link_libraries(Client ${KinAllLibs})