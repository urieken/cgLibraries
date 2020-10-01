#!/bin/sh
echo $CC
echo $CXX
if [ 0 -eq $# ]; then
	echo "SPECIFY COMPILER FAMILY"
elif [ 1 -eq $# ]; then
	echo "CHECKING COMPILER FAMILY"
	if [ 'gcc' == $1 ]; then
		echo "Setting gcc compiler family"
		export CC=/usr/bin/gcc
		export CXX=/usr/bin/g++
	elif [ 'clang' == $1 ]; then
		echo "Setting clang/llvm compiler family"
		export CC=/usr/bin/clang
		export CXX=/usr/bin/clang++
	else
		echo "Invalid option"
	fi
elif [ 1 -lt $# ]; then
	echo "TOO MANY ARGUMENTS"
fi
