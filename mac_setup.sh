#!/bin/bash
mkdir build
mkdir build/release
mkdir build/debug
cd build/release
cmake -GXcode -DCMAKE_BUILD_TYPE=Release ../../
cd ../debug
cmake -GXcode -DCMAKE_BUILD_TYPE=Debug ../../
cd ../../
