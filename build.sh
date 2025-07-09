#!/bin/bash

# Create a build directory if it doesn't exist
mkdir -p build

# Navigate into the build directory
cd build

# Run CMake to configure the project
cmake ..

# Run make to build the project
make 