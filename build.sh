#!/bin/bash

CPP_FILE="src/Controller.cpp src/main.cpp"

EXE_FILE="bin/xkontrol"

g++ -o $EXE_FILE $CPP_FILE
