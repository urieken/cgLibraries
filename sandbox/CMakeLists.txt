include(${CMAKE_CURRENT_SOURCE_DIR}/../toolchains/versions.cmake)

project(cgLibsSandbox
    VERSION 1.0
    DESCRIPTION "Crazy Galen's Libraries Sandbox"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(SOURCE_FILES
    src/main.cpp
    src/sandbox_app.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../cgl/inc)
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 cgl)
target_link_directories(${PROJECT_NAME} PRIVATE
    $ENV{MINGW_64_ROOT}/lib)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")