set(TEST_FILES
    src/app/app.cpp
    src/error/cgl_error.cpp
    tests/src/main.cpp
    tests/src/app_tests.cpp
    tests/src/event_tests.cpp)

add_executable(${PROJECT_NAME}_tests ${TEST_FILES})

target_include_directories(${PROJECT_NAME}_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../cgl/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendors/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendors/googletest/googlemock/include)
target_link_directories(${PROJECT_NAME}_tests PRIVATE
    $ENV{MINGW_64_ROOT}/lib
    ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME}_tests gtest gmock)

set_target_properties(${PROJECT_NAME}_tests
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
