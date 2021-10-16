cmake_minimum_required(VERSION 3.1...3.15)

message(STATUS "CMake version : ${CMAKE_VERSION}")

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.15)
endif()