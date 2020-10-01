if(NOT LLVM_COV_PATH)
    message(FATAL_ERROR "llvm-cov not found! Aborting...")
endif()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fprofile-instr-generate -fcoverage-mapping")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-instr-generate -fcoverage-mapping")

add_custom_target(${PROJECT_NAME}_tests-ccov-preprocessing
    COMMAND LLVM_PROFILE_FILE=${PROJECT_NAME}_tests.profraw
        $<TARGET_FILE:${PROJECT_NAME}_tests>
    COMMAND llvm-profdata merge -sparse ${PROJECT_NAME}_tests.profraw
        -o ${PROJECT_NAME}_tests.profdata
    DEPENDS ${PROJECT_NAME}_tests)

add_custom_target(${PROJECT_NAME}_tests-ccov-show
    COMMAND llvm-cov show $<TARGET_FILE:${PROJECT_NAME}_tests>
        -instr-profile=${PROJECT_NAME}_tests.profdata
        -show-line-counts-or-regions
    DEPENDS ${PROJECT_NAME}_tests-ccov-preprocessing)

add_custom_target(${PROJECT_NAME}_tests-ccov-report
    COMMAND llvm-cov report $<TARGET_FILE:${PROJECT_NAME}_tests>
        -instr-profile=${PROJECT_NAME}_tests.profdata
    DEPENDS ${PROJECT_NAME}_tests-ccov-preprocessing)

add_custom_target(${PROJECT_NAME}_tests-ccov
    COMMAND llvm-cov show $<TARGET_FILE:${PROJECT_NAME}_tests>
        -instr-profile=${PROJECT_NAME}_tests.profdata
        -show-line-counts-or-regions
        -output-dir=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}_tests-ccov
        -format="html"
    DEPENDS ${PROJECT_NAME}_tests-ccov-preprocessing)

add_custom_command(TARGET ${PROJECT_NAME}_tests-ccov POST_BUILD
    COMMAND;
    COMMENT "Open ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}-llvm-cov/index.html in your browser to view the coverage report.")

message("llvm-cov coverage set")
