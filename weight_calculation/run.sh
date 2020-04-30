#!/bin/bash

# Make build first
./build.sh

cd build

echo "=================================="
echo "Calculating term weights:"
echo "=================================="

time ./weight_calculation

echo "=================================="
echo "Calculation completed"
echo "=================================="
