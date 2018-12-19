cmake_minimum_required(VERSION 3.12)
project(webffmpeg)

set(CMAKE_CXX_STANDARD 17)

find_path(KinFrameworkPath KinCommonSetting.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${KinFrameworkPath})
#include(KinCommonSetting)

#find_package(KinBase)

if (DEFINED EMSCRIPTEN_VERSION)
    set(USE_EMSDK 1)
endif ()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

link_directories(${PROJECT_SOURCE_DIR}/libs)

include_directories(${PROJECT_SOURCE_DIR}/Source)

if (NOT USE_EMSDK)
    message("Not EMSDK")
else()
    message("USE EMSDK")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s USE_WEBGL2=1 --shell-file ${PROJECT_SOURCE_DIR}/Source/Example/ShellIndex.html")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s USE_WEBGL2=1 --shell-file ${PROJECT_SOURCE_DIR}/Source/Example/ShellIndex.html")

    SET(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

add_subdirectory(Source)