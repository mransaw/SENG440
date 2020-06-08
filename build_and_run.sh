#!/bin/bash
rm -rf bin
mkdir bin
#gcc math_utils/error_range.c math_utils/arctan.c -o bin/approx_error
gcc svd_main.c diagonalization/diagonalize.c math_utils/arctan.c math_utils/lin_cos.c math_utils/lin_sin.c -o bin/svd_main -Imath_utils -Idiagonalization

./bin/svd_main