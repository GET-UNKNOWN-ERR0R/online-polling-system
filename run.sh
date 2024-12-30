#!/bin/bash

g++ poll.cpp -o poll


if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."

    ./poll
else
    echo "Compilation failed. Please check the C++ code for errors."
fi
