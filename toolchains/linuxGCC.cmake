set(HEADER_PATHS
    include
    /usr/include/cairo
    /usr/include/gtk-3.0
    /usr/include/atk-1.0
    /usr/include/glib-2.0
    /usr/include/pango-1.0
    /usr/include/gstreamer-1.0
    /usr/include/gdk-pixbuf-2.0
    /usr/lib/x86_64-linux-gnu/glib-2.0/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common/include)

set(LINK_LIBRARY_PATHS
    $ENV{MINGW_64_ROOT}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../build/lib)

set(LINK_LIBS
    gstreamer-1.0 glib-2.0 gtk-3 X11 gdk-3 gobject-2.0 cairo gstvideo-1.0 SDL2main SDL2 cgl)

message(STATUS "minGWGCC.cmake")
