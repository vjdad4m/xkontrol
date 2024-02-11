#!/bin/bash

mkdir -p build

cmake -S . -B build
cmake --build build

# mkdir -p bin

# CPP_FILE="src/Controller.cpp src/main.cpp"

# EXE_FILE="bin/xkontrol"

# if [[ "$OSTYPE" == "linux-gnu"* ]]; then
#   g++ -o $EXE_FILE $CPP_FILE 
# elif [[ "$OSTYPE" == "msys" ]]; then
#   g++ -o $EXE_FILE $CPP_FILE -lXInput -std=c++2a
# else
#   echo "Unsupported OS $OSTYPE"
# fi
