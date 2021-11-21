cmake_minimum_required(VERSION 3.10)

set (CMAKE_COLOR_MAKEFILE ON)

project(exo_video_asciifyer)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(3RDPARTY_DIR "3rdparty")
set(ZMQ_DIR "${3RDPARTY_DIR}/libzmq")
set(OPENCV_DIR "${3RDPARTY_DIR}/opencv")

add_subdirectory(${ZMQ_DIR})
add_subdirectory(${OPENCV_DIR})

include_directories("${OPENCV_DIR}/include")

find_package(OpenCV REQUIRED)

add_executable(exo_video_asciifyer asciifyer.cpp)

target_link_libraries(exo_video_asciifyer ${OpenCV_LIBS})
