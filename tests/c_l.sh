#!/bin/bash

# Count all source files
find . -name "*.c" -o -name "*.h" | xargs wc -l

# For detailed breakdown by file type:
echo "C source files:"
find . -name "*.c" | xargs wc -l
echo -e "\nHeader files:"
find . -name "*.h" | xargs wc -l

# For just total count:
find . -name "*.c" -o -name "*.h" | xargs wc -l | tail -n 1
