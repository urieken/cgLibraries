if(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    message(WARNING "Optimized(non-Debug) build may yield misleading results")
endif()
if(NOT LCOV_PATH)
    message(FATAL_ERROR "lcov not found! Aborting...")
endif()
if(NOT GENHTML_PATH)
    message(FATAL_ERROR "genhtml not found! Aborting...")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --coverage -fprofile-arcs -ftest-coverage")

set(COVERAGE_DIR "${CMAKE_CURRENT_BINARY_DIR}/../../coverage")
set(COVERAGE_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/cgl_tests.dir/src")

add_custom_target(${PROJECT_NAME}_tests-ccov-preprocessing
    COMMAND $<TARGET_FILE:${PROJECT_NAME}_tests>
    COMMAND mkdir -p ${COVERAGE_DIR}/data
    COMMAND mkdir -p ${COVERAGE_DIR}/info
    COMMAND mkdir -p ${COVERAGE_DIR}/report
    COMMENT "PREPROCESSING"
    DEPENDS ${PROJECT_NAME}_tests)

add_custom_target(${PROJECT_NAME}_tests-ccov-report
    COMMAND $<TARGET_FILE:${PROJECT_NAME}_tests>
    COMMAND cp -R ${COVERAGE_SOURCE_DIR}/app ${COVERAGE_DIR}/data
    COMMAND cp -R ${COVERAGE_SOURCE_DIR}/error ${COVERAGE_DIR}/data
    COMMAND lcov -c -d ${COVERAGE_DIR}/data -o ${COVERAGE_DIR}/info/cgl_tests.info
    COMMAND lcov --remove ${COVERAGE_DIR}/info/cgl_tests.info '/usr/*'
        -o ${COVERAGE_DIR}/info/cgl_tests_final.info
    COMMAND genhtml -o ${COVERAGE_DIR}/report ${COVERAGE_DIR}/info/cgl_tests_final.info
    # COMMAND firefox ${CMAKE_CURRENT_BINARY_DIR}/../../coverage/report/index.html
    COMMENT "REPORT"
    DEPENDS ${PROJECT_NAME}_tests-ccov-preprocessing)

add_custom_command(TARGET ${PROJECT_NAME}_tests-ccov-report POST_BUILD
    COMMAND;
    COMMENT "GENERATING COVERAGE REPORTS")

message("lcov coverage set")
