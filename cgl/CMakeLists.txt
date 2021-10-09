include(${CMAKE_CURRENT_SOURCE_DIR}/../toolchains/versions.cmake)

project(cgl
    VERSION 1.0
    DESCRIPTION "Crazy Galen's Library"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_subdirectory(library)

include(${CMAKE_CURRENT_SOURCE_DIR}/../toolchains/buildTypes.cmake)

