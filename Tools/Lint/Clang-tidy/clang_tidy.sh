#!/bin/bash

CPP_H_FILES=$(find . -type f \( -name "*.cpp" -o -name "*.h" \))

echo "Running clang-tidy with the following checks"

clang-tidy-11 --list-checks || exit $?

clang-tidy-11 $CPP_H_FILES || exit $?

echo "Done"
