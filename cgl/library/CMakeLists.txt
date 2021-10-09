include(${CMAKE_CURRENT_SOURCE_DIR}/../../toolchains/versions.cmake)

project(CGLCommon
    VERSION 1.0
    DESCRIPTION "Crazy Galen's Library - Common"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/application/SDLApplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/event/CoreEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/event/SDLEventListener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/system/Compilers.cpp)

add_library(${PROJECT_NAME}
    ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${PROJECT_NAME}
    SDL2main SDL2)
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(${PROJECT_NAME}_sandbox
    ${SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/sandbox/main.cpp)
target_include_directories(${PROJECT_NAME}_sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}_sandbox
    SDL2main SDL2 ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_sandbox
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/AppRunner.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/Compilers.test.cpp)

add_executable(${PROJECT_NAME}_test
    ${TEST_FILES}
    ${SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/main.cpp)
target_include_directories(${PROJECT_NAME}_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/test/mock
    /opt/googletest/include)
target_link_directories(${PROJECT_NAME}_test PRIVATE
    ${CMAKE_BINARY_DIR}/lib
    /opt/googletest/lib)
target_link_libraries(${PROJECT_NAME}_test
    SDL2main SDL2 gtest gmock pthread)
set_target_properties(${PROJECT_NAME}_test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
