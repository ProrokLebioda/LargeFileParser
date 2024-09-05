#!/bin/bash

cmake -B ./build
cmake --install ./build --config Release
cd build/
make