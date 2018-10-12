cmake_minimum_required(VERSION 3.12)
project(Example)

set(CMAKE_CXX_STANDARD 17)

add_executable(ExampleClient eClient.cpp)
add_executable(ExampleServer eServer.cpp)

target_link_libraries(ExampleClient Client)
target_link_libraries(ExampleServer Server)