cmake_minimum_required(VERSION 3.24)
project(Group-17)
set(CMAKE_CXX_STANDARD 17)

################################################################
# Find and include GTKMM library
################################################################

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
link_libraries(${GTKMM_LIBRARIES})

################################################################
# Find and include OpenCV Library
################################################################

find_package(OpenCV CONFIG REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})
link_libraries(${OpenCV_LIBS})

################################################################
# Find and include Wt Library
################################################################

find_package(Wt REQUIRED)

SET(BOOST_LIBS
        boost_system
        boost_thread
        boost_filesystem
        boost_program_options
        )

################################################################
# Add Project-Created Headers
################################################################

# Find all header files in the include/ directory
file(GLOB HEADER_FILES include/*.hpp)

# Add all header files as library targets
add_library(HEADERS ${HEADER_FILES})

# Must set the linker language for these headers to CXX, otherwise an error occurs
set_target_properties(HEADERS PROPERTIES LINKER_LANGUAGE CXX)

################################################################
# Add Project-Created Source Files
################################################################

# Find all source (.cpp) files in the src/ directory
file(GLOB SOURCE_FILES src/*.cpp)

## Add all source (.cpp) files as executable targets
add_executable(Group-17 ${SOURCE_FILES})

################################################################
# Link External Libraries
################################################################

target_link_libraries(Group-17 ${OpenCV_LIBS} ${GTKMM_LIBRARIES} wt
        wthttp
        ${WT_DBO_CONNECTOR}
        ${BOOST_LIBS})

################################################################
