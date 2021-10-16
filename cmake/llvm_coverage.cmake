find_package(LLVM REQUIRED CONFIG)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-instr-generate -fcoverage-mapping")

set(COVERAGE_DIR "${CMAKE_CURRENT_BINARY_DIR}/../../coverage")

add_custom_target(${PROJECT_NAME}_test-ccov-preprocessing
    COMMAND LLVM_PROFILE_FILE=${PROJECT_NAME}_test.profraw
        $<TARGET_FILE:${PROJECT_NAME}_test>
    COMMAND llvm-profdata-10 merge -sparse ${PROJECT_NAME}_test.profraw
        -o ${PROJECT_NAME}_test.profdata
    DEPENDS ${PROJECT_NAME}_test)

add_custom_target(${PROJECT_NAME}_test-ccov-show
    COMMAND llvm-cov-10 show $<TARGET_FILE:${PROJECT_NAME}_test>
        -instr-profile=${PROJECT_NAME}_test.profdata
        -show-line-counts-or-regions
        -ignore-filename-regex="opt/*|test/*"
    DEPENDS ${PROJECT_NAME}_test-ccov-preprocessing)

add_custom_target(${PROJECT_NAME}_test-ccov-report
    COMMAND llvm-cov-10 report $<TARGET_FILE:${PROJECT_NAME}_test>
        -instr-profile=${PROJECT_NAME}_test.profdata
        -ignore-filename-regex="opt/*|test/*"
    DEPENDS ${PROJECT_NAME}_test-ccov-preprocessing)

add_custom_target(${PROJECT_NAME}_test-ccov
    COMMAND llvm-cov-10 show $<TARGET_FILE:${PROJECT_NAME}_test>
        -instr-profile=${PROJECT_NAME}_test.profdata
        -show-line-counts-or-regions
        -ignore-filename-regex="opt/*|test/*"
        -output-dir=${COVERAGE_DIR}/report
        -format="html"
    DEPENDS ${PROJECT_NAME}_test-ccov-preprocessing)

add_custom_command(TARGET ${PROJECT_NAME}_test-ccov POST_BUILD
    COMMAND;
    COMMENT "Open ${COVERAGE_DIR}/report-llvm-cov/index.html in your browser to view the coverage report.")

message(STATUS "Added custom target ${PROJECT_NAME}_test-ccov-preprocessing")
message(STATUS "Added custom target ${PROJECT_NAME}_test-ccov")
message(STATUS "Added custom target ${PROJECT_NAME}_test-ccov-show")
message(STATUS "Added custom target ${PROJECT_NAME}_test-ccov-report")