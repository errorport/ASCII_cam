cmake_minimum_required(VERSION 3.10)

set (CMAKE_COLOR_MAKEFILE ON)

project(exo_video_asciifyer)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

set(CMAKE_CXX_FLAGS "-O3 -w -std=c++11")
set(3RDPARTY_DIR "3rdparty")
set(ZMQ_3RD_DIR "${3RDPARTY_DIR}/libzmq")

add_subdirectory(${ZMQ_3RD_DIR})

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(".")
add_executable(exo_video_asciifyer asciifyer.cpp config.hpp)

target_link_libraries(exo_video_asciifyer ${OpenCV_LIBS})
