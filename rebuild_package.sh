#!/bin/sh
BUILD_DIR="build"
if [ ! -d "$BUILD_DIR" ]; then
	echo "DIR NOT FOUND"
	mkdir ${BUILD_DIR}
else
	echo "DIR FOUND"
fi
pushd "$BUILD_DIR"
LCOV_PATH=`which lcov`
echo ${LCOV_PATH}
GENHTML_PATH=`which genhtml`
echo ${GENHTML_PATH}
LLVM_COV_PATH=`which llvm-cov`
echo ${LLVM_COV_PATH}
cmake -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug -DLLVM_COV_PATH=${LLVM_COV_PATH} -DLCOV_PATH=${LCOV_PATH} -DGENHTML_PATH=${GENHTML_PATH} -DBUILD_DEPENDENCIES=ON ..
make
make cgl_tests-ccov-report
#make cgl_tests-ccov
#pushd bin
#./cgl_tests
#popd
popd
