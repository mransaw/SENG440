#!/bin/bash
rm -rf bin
mkdir bin
gcc tests/diagonalize_tests.c diagonalization/diagonalize.c math_utils/arctan.c math_utils/lin_cos.c math_utils/lin_sin.c -o bin/diagonalize_tests -Imath_utils -Idiagonalization -lm

./bin/diagonalize_tests
