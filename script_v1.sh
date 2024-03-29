#!/bin/bash

# Loop over all files in tests/logs_in ending in ,in
for file in lotan_tests/logs_in/*.in; do
    # Get the base name of the file
    base_name=$(basename "$file" .in)
    
    # Run the ./main program with the input file and redirect the output to tests/logs_myout
    echo "now doing ${file}"
    ./a.out < "$file" > "lotan_tests/logs_myout/${base_name}.out"
    # Diff the output file with the expected output file, ignoring space changes
    diff_output=$(diff -w "lotan_tests/logs_myout/${base_name}.out" "lotan_tests/logs_out/${base_name}.out")
    if [ $? -ne 0 ]; then
        echo "${file} fail"
    fi
done