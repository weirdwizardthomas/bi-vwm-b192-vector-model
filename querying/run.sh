#!/bin/bash

# Build
./build.sh

cd build

# Launch
./Querying --docroot ./../resources --http-address 0.0.0.0 --http-port 3999
