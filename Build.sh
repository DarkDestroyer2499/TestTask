#!/bin/bash
mkdir -p build
cd build

cmake ..

cmake --build .

echo "Press any key to continue..."
read -n 1 -s
