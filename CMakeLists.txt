cmake_minimum_required(VERSION 3.24)
project(Group-17)
set(CMAKE_CXX_STANDARD 17)

################################################################
# cairomm
################################################################

include_directories(include/cairomm-1.0)
link_directories(lib/cairomm-1.0)

################################################################
# gtkmm
################################################################

include_directories(include/gtkmm-3.0)
link_directories(lib/gtkmm-3.0)

################################################################
# opencv4
################################################################

include_directories(include/opencv4)
link_directories(lib/opencv4)

################################################################
# glibmm
################################################################

include_directories(include/glibmm-2.4)
link_directories(lib/glibmm-2.4)

################################################################
# glib
################################################################

include_directories(include/glib-2.0)
link_directories(lib/glib-2.0)

################################################################
# sigc++
################################################################

include_directories(include/sigc++-2.0)
link_directories(lib/sigc++-2.0)

################################################################
# giomm
################################################################

include_directories(include/giomm-2.4)
link_directories(lib/giomm-2.4)

################################################################
# gdkmm
################################################################

include_directories(include/gdkmm-3.0)
link_directories(lib/gdkmm-3.0)

################################################################
# pangomm
################################################################

include_directories(include/pangomm-1.4)
link_directories(lib/pangomm-1.4)

################################################################
# gtk
################################################################

include_directories(include/gtk-3.0)
link_directories(lib/gtk-3.0)

################################################################
# pango
################################################################

include_directories(include/pango-1.0)
link_directories(lib/pango-1.0)

################################################################
# harfbuzz
################################################################

include_directories(include/harfbuzz)
link_directories(lib/harfbuzz)

################################################################
# cairo
################################################################

include_directories(include/cairo)
link_directories(lib/cairo)

################################################################
# gdk-pixbuf
################################################################

include_directories(include/gdk-pixbuf-2.0)
link_directories(lib/gdk-pixbuf-2.0)

################################################################
# freetype2
################################################################

include_directories(include/freetype2)
link_directories(lib/freetype2)

################################################################
# atkmm
################################################################

include_directories(include/atkmm-1.6)
link_directories(lib/atkmm-1.6)

################################################################
# atk
################################################################

include_directories(include/atk-1.0)
link_directories(lib/atk-1.0)

################################################################
# fontconfig
################################################################

include_directories(include/fontconfig)
link_directories(lib/fontconfig)


################################################################
# Wt wt-4.9.1
################################################################
find_package(Wt REQUIRED)
include_directories(${WT_INCLUDE_DIR})


################################################################
# Project-Created Headers
################################################################

## Find all header files in the include/ directory
#file(GLOB HEADER_FILES include/*.hpp)

### Find all header files in the include/ directory
#file(GLOB HEADER_FILES include/*.hpp)
#
## Add all header files as library targets
#add_library(HEADERS ${HEADER_FILES})
#
## Must set the linker language for these headers to CXX, otherwise an error occurs
#set_target_properties(HEADERS PROPERTIES LINKER_LANGUAGE CXX)

set(INCLUDE_DIR /include)

include_directories(INCLUDE_DIR)

################################################################
# Project-Created Source Files
################################################################

# Find all source (.cpp) files in the src/ directory
file(GLOB SOURCE_FILES src/CircularBuffer.cpp src/*.cpp)

# Add all source (.cpp) files as executable targets
add_executable(Group-17 ${SOURCE_FILES} src/WebApp.cpp src/WebApp.cpp src/WebApp.cpp)

################################################################
# Link Library Binaries
################################################################

target_link_libraries(Group-17 gtkmm-3.0
        opencv_highgui opencv_videoio opencv_imgproc opencv_core
        atkmm-1.6 gdkmm-3.0 giomm-2.4 gtk-3 gdk-3 atk-1.0
        cairo-gobject gio-2.0 pangomm-1.4 glibmm-2.4 cairomm-1.0 sigc-2.0
        pangocairo-1.0 pango-1.0 harfbuzz cairo gdk_pixbuf-2.0 gobject-2.0
        glib-2.0 Wt::Wt Wt::HTTP)

################################################################