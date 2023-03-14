cmake_minimum_required(VERSION 3.24)
project(33307B_Group_17_Project)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
link_libraries(${GTKMM_LIBRARIES})

add_executable(33307B_Group_17_Project
        Main.cpp
        VideoRecorder.hpp
        VideoRecorder.cpp gui.h gui.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( 33307B_Group_17_Project ${OpenCV_LIBS} ${GTKMM_LIBRARIES})
