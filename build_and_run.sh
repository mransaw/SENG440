#!/bin/bash
rm -rf bin
mkdir bin
gcc math_utils/error_range.c math_utils/arctan.c -o bin/approx_error
./bin/approx_error