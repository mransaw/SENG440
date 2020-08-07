rm -rf asm
mkdir asm

gcc int_main.c diagonalization/diagonalize.c math_utils/arctan2.c -S -Imath_utils -Idiagonalization -lm -ftree-vectorize -mfpu=neon -mcpu=generic-armv7-a -O3
mv int_main.s asm
mv diagonalize.s asm
mv arctan2.s asm