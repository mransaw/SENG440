#!/bin/bash
rm -rf bin
mkdir bin
clear
clear

#gcc int_main.c diagonalization/diagonalize.c math_utils/arctan2.c math_utils/lin_cos.c math_utils/lin_sin.c -o bin/int_main -Imath_utils -Idiagonalization -lm
gcc int_main.c diagonalization/diagonalize.c math_utils/arctan2.c -S bin/testing -Imath_utils -Idiagonalization -lm -ftree-vectorize -mfpu=neon -mcpu=generic-armv7-a -O3
./bin/testing

#gcc math_utils/error_range.c math_utils/lin_sin.c math_utils/lin_cos.c math_utils/arctan.c -o bin/error_range
#./bin/error_range