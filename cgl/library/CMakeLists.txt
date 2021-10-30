set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

include(versions)

project(CGLCommon
    VERSION 1.0
    DESCRIPTION "Crazy Galen's Library - Common"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(CODE_COVERAGE "On")
set(CMAKE_BUILD_TYPE "Debug")

include(build_types)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/application/SDLApplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/command/SDLRendererCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/command/SDLRendererCopyCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/display/SDLRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/display/SDLTexture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/display/SDLWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/error/CGLError.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/event/IEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/event/CoreEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/event/SDLEventListener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/event/SDLEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/system/Arguments.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/system/Compilers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/system/KeyPairString.cpp)

add_library(${PROJECT_NAME}
    ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${PROJECT_NAME}
    SDL2main SDL2 SDL2_image)
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
    SDL2main SDL2 SDL2_image ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_sandbox
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/integration/SDLApplication.integration.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/integration/SDLEventListener.integration.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/integration/SDLRenderer.integration.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/integration/SDLWindow.integration.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/unit/AppRunner.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/unit/Arguments.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/unit/CGLError.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/unit/Compilers.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/unit/CoreEvent.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/unit/KeyPairString.test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/source/unit/SDLEvent.test.cpp)

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
    SDL2main SDL2 SDL2_image gtest gmock pthread)
set_target_properties(${PROJECT_NAME}_test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_custom_target(${PROJECT_NAME}_post-processing
    COMMAND cp -rv ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/bin
    DEPENDS ${PROJECT_NAME}_sandbox)

add_custom_target(${PROJECT_NAME}_sandbox_execute
    COMMAND $<TARGET_FILE:${PROJECT_NAME}_sandbox>
    DEPENDS ${PROJECT_NAME}_post-processing)
