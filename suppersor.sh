#!/bin/bash

# Check if a file is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <valgrind.log>"
    exit 1
fi

LOGFILE="$1"

# Extract suppressions from the log
awk '
  /^{/ { capture=1 }  # Start capturing when "{" is found
  capture { print }   # Print the line if capturing is active
  /^}/ { capture=0 }  # Stop capturing when "}" is found
' "$LOGFILE"
