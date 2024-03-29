if(CODE_COVERAGE)
    message(STATUS "Building with instrumentation")
    if(CMAKE_COMPILER_IS_GNUCXX)
        message(STATUS "Building with GNUCXX")
        include(lcov_coverage)
    elseif("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR
        "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
        message(STATUS "Building with CLANG")    
        include(llvm_coverage)
    endif()
else()
    message(STATUS "Building without instrumentation")
endif()
