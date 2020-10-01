set(SOURCE_FILES
    src/app/app.cpp
    src/error/cgl_error.cpp
    src/compilers/compilers.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
    inc)
target_link_directories(${PROJECT_NAME} PRIVATE
    $ENV{MINGW_64_ROOT}/lib
    ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
