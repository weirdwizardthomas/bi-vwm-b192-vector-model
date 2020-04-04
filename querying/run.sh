#!/bin/bash

# Exit on first error
set -e

# Create dir build
mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build
cmake --build .

# Launch
./Querying --docroot ./../resources --http-address 0.0.0.0 --http-port 3999
