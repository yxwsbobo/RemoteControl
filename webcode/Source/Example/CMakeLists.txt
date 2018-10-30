cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

add_executable(webffmpeg main.cpp WapSdl.cpp WapSdl.h WapFFmpeg.cpp WapFFmpeg.h JsFunctions.h)

target_link_libraries(webffmpeg libavcodec libavutil libswscale )

add_custom_command(TARGET webffmpeg PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Source/Example/DependJs/ $<TARGET_FILE_DIR:webffmpeg>)

if (USE_EMSDK)
    em_link_js_library(webffmpeg "InnerScript.js")
endif()