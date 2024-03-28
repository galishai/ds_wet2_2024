#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' 
passed=0
failed=0

for file in lotan_tests/logs_in/test_1.in; do
    filename=$(basename -- "$file")

    valgrind -q -s --leak-check=yes --show-leak-kinds=all ./a.out < "$file" > temp.txt

    diff -q temp.txt "lotan_tests/logs_out/${filename%.*}.out"

    if [ $? -eq 0 ]; then
        passed=$(( passed + 1 ))
        echo -e "Test $filename ${GREEN}passed${NC}"
    else
        failed=$(( failed + 1 ))
        echo -e "Test $filename ${RED}failed${NC}"
    fi
done

echo -e "Passed tests: ${GREEN}$passed${NC}"
echo -e "Failed tests: ${RED}$failed${NC}"