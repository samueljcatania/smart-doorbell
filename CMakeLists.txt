cmake_minimum_required(VERSION 3.24)
project(33307B_Group_17_Project)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
find_package(OpenCV 4.0.0 REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

link_directories(${GTKMM_LIBRARY_DIRS})
link_libraries(${GTKMM_LIBRARIES})

add_executable(33307B_Group_17_Project
        src/Main.cpp
        src/Camera.cpp
        src/DisplayWindow.cpp
        src/Doorbell.cpp
        src/VideoRecorder.cpp
        include/Camera.h
        include/DisplayWindow.h
        include/Doorbell.h
        include/VideoRecorder.h include/asda.cpp include/asda.h asfasa.cpp asfasa.h)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(33307B_Group_17_Project ${OpenCV_LIBS} ${GTKMM_LIBRARIES} ${GTK3_LIBRARIES})

