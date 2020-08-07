/opt/arm/4.3.2/bin/arm-linux-gcc -static diagonalization/diagonalize.c math_utils/arctan2.c math_utils/lin_cos.c math_utils/lin_sin.c -o bin/int_main.exe -Imath_utils -Idiagonalization -lm
./bin/int_main.exe
