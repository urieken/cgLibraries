cmake_minimum_required(VERSION 3.1...3.15)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.15)
endif()

project(vendors
    VERSION 1.0
    DESCRIPTION "3rd party vendors"
    LANGUAGES CXX)
add_subdirectory(googletest)
add_subdirectory(benchmark)
add_subdirectory(imgui)