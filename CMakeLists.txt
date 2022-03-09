cmake_minimum_required(VERSION 3.1...3.15)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.15)
endif()

project(cgLibraries
    VERSION 1.0
    DESCRIPTION "Crazy Galen's Libraries"
    LANGUAGES CXX)
if(BUILD_DEPENDENCIES)
    # add_subdirectory(vendors/Vulkan-Headers)
    # add_subdirectory(vendors/googletest)
    # add_subdirectory(vendors/imgui)
    # add_subdirectory(vendors/SDL2)
endif()
    add_subdirectory(vendors/googletest)
    add_subdirectory(vendors/imgui)
add_subdirectory(cgl)
# if(NOT CODE_COVERAGE)
#     add_subdirectory(sandbox)
# endif()
