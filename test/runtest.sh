#!/bin/bash
export GTEST_COLOR="yes" 
export TERM="xterm-color"
cmake -S . -B build
cmake --build build
ctest -V --test-dir build/test --output-on-failure -j12
#./build/test/Debug/TestExecutable