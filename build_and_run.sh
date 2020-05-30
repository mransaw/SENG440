#!/bin/bash
rm -rf bin
mkdir bin
#gcc math_utils/error_range.c math_utils/arctan.c -o bin/approx_error
gcc diagonalization/diagonalize.c math_utils/arctan.c -o bin/diagonalize -Imath_utils

./bin/diagonalize