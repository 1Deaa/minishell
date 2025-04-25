#!/bin/bash

# Run make command
make

# Check if make succeeded
if [ $? -ne 0 ]; then
    echo "Make failed. Exiting with error code."
    exit 1
else
    echo "Make succeeded."
    exit 0
fi
