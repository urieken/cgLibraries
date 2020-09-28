set(HEADER_PATHS
    include
    $ENV{MINGW_64_ROOT}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common/include)

set(LINK_LIBRARY_PATHS
    $ENV{MINGW_64_ROOT}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../build/lib)

set(LINK_LIBS
    mingw32 SDL2main SDL2 cgl)

message(STATUS "minGWGCC.cmake")
