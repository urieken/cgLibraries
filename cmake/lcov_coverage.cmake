if (NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    message(WARNING "Optimized(non-debug) build may yield misleading results")
endif()

find_program(LCOV_BIN lcov)
if(LCOV_BIN MATCHES "lcov$")
    message(STATUS "lcov found in ${LCOV_BIN}")
else()
    message(FATAL_ERROR "lcov not found! Aborting...")
endif()

find_program(GENHTML_BIN genhtml)
if(GENHTML_BIN MATCHES "genhtml$")
    message(STATUS "genhtml found in ${GENHTML_BIN}")
else()
    message(FATAL_ERROR "genhtml not found! Aborting...")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --coverage -fprofile-arcs -ftest-coverage")

set(COVERAGE_DIR "${CMAKE_CURRENT_BINARY_DIR}/../../coverage")
set(COVERAGE_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}_test.dir/source")

add_custom_target(${PROJECT_NAME}_test-ccov-preprocessing
    COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>
    COMMAND mkdir -p ${COVERAGE_DIR}/data
    COMMAND mkdir -p ${COVERAGE_DIR}/info
    COMMAND mkdir -p ${COVERAGE_DIR}/report
    COMMENT "preprocessing"
    DEPENDS ${PROJECT_NAME}_test)

add_custom_target(${PROJECT_NAME}_test-ccov-report
    COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>
    COMMAND cp -R ${COVERAGE_SOURCE_DIR} ${COVERAGE_DIR}/data
    COMMAND lcov -c -d ${COVERAGE_DIR}/data -o ${COVERAGE_DIR}/info/${PROJECT_NAME}_test.info
    COMMAND lcov --remove ${COVERAGE_DIR}/info/${PROJECT_NAME}_test.info '/usr/*'
        -o ${COVERAGE_DIR}/info/${PROJECT_NAME}_test_stripped.info
    COMMAND genhtml -o ${COVERAGE_DIR}/report ${COVERAGE_DIR}/info/${PROJECT_NAME}_test_stripped.info
    COMMENT "report"
    DEPENDS ${PROJECT_NAME}_test-ccov-preprocessing)

add_custom_command(TARGET ${PROJECT_NAME}_test-ccov-report POST_BUILD
     COMMAND;
     COMMENT "generating coverage reports")

message(STATUS "Added custom target ${PROJECT_NAME}_test-ccov-preprocessing")
message(STATUS "Added custom target ${PROJECT_NAME}_test-ccov-report")