#!/bin/sh

set -x

SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-./build}
CXX=${CXX:-g++}

mkdir -p $BUILD_DIR \
  && cd $BUILD_DIR \
  && cmake \
           -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
           $SOURCE_DIR \
  && make $*

# Use the following command to run all the unit tests
# at the dir $BUILD_DIR:
# CTEST_OUTPUT_ON_FAILURE=TRUE make test

# cd $SOURCE_DIR && doxygen

