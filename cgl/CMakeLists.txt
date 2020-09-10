cmake_minimum_required(VERSION 3.1...3.15)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.15)
endif()

project(cgl
    VERSION 1.0
    DESCRIPTION "Crazy Galen's Library"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(SOURCE_FILES
    src/app/app.cpp
    src/compilers/compilers.cpp)

set(TEST_FILES
    src/app/app.cpp
    tests/src/main.cpp
    tests/src/app_tests.cpp
    tests/src/event_tests.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    inc)

add_executable(${PROJECT_NAME}_tests ${TEST_FILES})
target_include_directories(${PROJECT_NAME}_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../cgl/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendors/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendors/googletest/googlemock/include)
target_link_directories(${PROJECT_NAME}_tests PRIVATE
    $ENV{MINGW_64_ROOT}/lib
    ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME}_tests gtest gmock)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set_target_properties(${PROJECT_NAME}_tests
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")