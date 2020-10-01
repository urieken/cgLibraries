#!/bin/sh
COVERAGE_DIR="coverage"
if [ ! -d "$COVERAGE_DIR" ]; then
	echo "DIR NOT FOUND"
	mkdir -p ${COVERAGE_DIR}/data
	mkdir -p ${COVERAGE_DIR}/info
	mkdir -p ${COVERAGE_DIR}/report
else
	echo "DIR FOUND"
fi
if [ '/usr/bin/gcc' == ${CC} ]; then
	echo "Generating coverage with lcov"
	cp -v -R build/cgl/CMakeFiles/cgl_tests.dir/src/app ${COVERAGE_DIR}/data
	cp -v -R build/cgl/CMakeFiles/cgl_tests.dir/src/error ${COVERAGE_DIR}/data
	pushd ${COVERAGE_DIR}/report
	lcov -c -d ../data -o ../info/cgl_tests.info
	lcov -r ../info/cgl_tests.info /usr\* -o ../info/cgl_tests_final.info
	genhtml -o . ../info/cgl_tests_final.info
	popd
elif [ '/usr/bin/clang' == ${CC} ]; then
	echo "Generating coverage with llvm-cov"
	pushd ${COVERAGE_DIR}/report
	LLVM_PROFILE_FILE=cgl_tests.profraw ./../../build/bin/cgl_tests
        llvm-profdata merge -sparse cgl_tests.profraw -o cgl_tests.profdata
	llvm-cov show ./../../build/bin/cgl_tests -instr-profile=cgl_tests.profdata -show-line-counts-or-regions 
	llvm-cov report ./../../build/bin/cgl_tests -instr-profile=cgl_tests.profdata
	llvm-cov show ./../../build/bin/cgl_tests -instr-profile=cgl_tests.profdata -show-line-counts-or-regions -output-dir=. -format="html"
	popd
fi
