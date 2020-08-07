#!/bin/bash
rm -rf bin
mkdir bin
clear
clear
#gcc tests/diagonalize_tests.c diagonalization/diagonalize.c math_utils/arctan.c math_utils/lin_cos.c math_utils/lin_sin.c -o bin/diagonalize_tests -Imath_utils -Idiagonalization -lm
#./bin/diagonalize_tests
gcc tests/linear_approx_tests.c math_utils/arctan2.c math_utils/lin_cos.c math_utils/lin_sin.c -o bin/linear_approx_tests -Imath_utils -lm
./bin/linear_approx_tests