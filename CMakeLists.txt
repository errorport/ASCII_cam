cmake_minimum_required(VERSION 3.10)

set (CMAKE_COLOR_MAKEFILE ON)

project(exo_video_asciifyer)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

set(3RDPARTY_DIR "3rdparty")
set(ZMQ_3RD_DIR "${3RDPARTY_DIR}/libzmq")

find_package(OpenCV REQUIRED)

add_subdirectory(${ZMQ_3RD_DIR})

include_directories("${OpenCV_LIBS}/include")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(exo_video_asciifyer asciifyer.cpp)

target_link_libraries(exo_video_asciifyer ${OpenCV_LIBS})
