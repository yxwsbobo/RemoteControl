cmake_minimum_required(VERSION 3.12)
project(RCMaster)

set(CMAKE_CXX_STANDARD 17)

if (DEFINED EMSCRIPTEN_VERSION)
    set(USE_EMSDK 1)
endif ()

if (USE_EMSDK)
    message("USE EMSDK")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s USE_WEBGL2=1 --shell-file ${PROJECT_SOURCE_DIR}/Source/Example/ShellIndex.html")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s USE_WEBGL2=1 --shell-file ${PROJECT_SOURCE_DIR}/Source/Example/ShellIndex.html")

    SET(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

add_library(RCMaster RCMaster.cpp RCMaster.h)

if(NOT USE_EMSDK)
    target_link_libraries(RCMaster ${KinAllLibs})
else()
    target_link_libraries(RCMaster libavcodec libavutil libswscale)
endif()

