cmake_minimum_required(VERSION 3.24)
project(Group-17)
set(CMAKE_CXX_STANDARD 17)


################################################################
# Find and include OpenCV Library
################################################################

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-4.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
link_libraries(${GTKMM_LIBRARIES})

# Find Package
find_package(OpenCV REQUIRED)

# Additional Include Directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Additional Library Directories
link_directories(${OpenCV_LIB_DIR})

################################################################
# Find and include GTKMM library
################################################################


################################################################
# Link External Libraries
################################################################

################################################################
# Project-Created Headers
################################################################

# Find all header files in the include/ directory
file(GLOB HEADER_FILES include/*.hpp)

# Add all header files as library targets
add_library(HEADERS ${HEADER_FILES})

# Must set the linker language for these headers to CXX, otherwise an error occurs
set_target_properties(HEADERS PROPERTIES LINKER_LANGUAGE CXX)

################################################################
# Project-Created Source Files
################################################################

# Find all source (.cpp) files in the src/ directory
file(GLOB SOURCE_FILES src/*.cpp)

## Add all source (.cpp) files as executable targets
add_executable(Group-17 ${SOURCE_FILES})

#target_link_libraries(Group-17 ${OpenCV_LIBS} ${GTKMM_LIBRARIES})
target_link_libraries(Group-17 ${OpenCV_LIBS})


################################################################
