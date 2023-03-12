cmake_minimum_required(VERSION 3.24)
project(33307B_Group_17_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(33307B_Group_17_Project
        Main.cpp
        VideoRecorder.hpp
        VideoRecorder.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( 33307B_Group_17_Project ${OpenCV_LIBS} )