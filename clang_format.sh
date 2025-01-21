#!/bin/bash

# Directories to process
directories=("apps")

# Log file
log_file="clang-format.log"
> "$log_file" # Clear the log file

# Loop through each directory
for dir in "${directories[@]}"; do
    # Find all main.c files in the current directory and its subdirectories, excluding the build folder
    files=$(find "$dir" -type d -name "build" -prune -o -type f -name "main.c" -print)

    if [ -z "$files" ]; then
        echo "No main.c files found for formatting in $dir." | tee -a "$log_file"
    else
        for file in $files; do
            echo "Formatting file: $file" | tee -a "$log_file"
            if clang-format -i -style=file "$file" 2>&1 | tee -a "$log_file"; then
                echo "Formatted file: $file" | tee -a "$log_file"
            else
                echo "Error formatting file: $file" | tee -a "$log_file"
            fi
        done
    fi
done
