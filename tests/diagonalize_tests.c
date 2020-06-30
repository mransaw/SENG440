#include <linear_approx.h>
#include <assert.h>
#include <stdio.h>
#include <diagonalize.h>
#include <stdlib.h>

#define PI 0x7FFFFFFF

void arctan_test() {
    int X = 1030;
    int theta = arctan(X);
    assert(theta == (1319*X+291));
}

void sine_test() {
    int result;
    
    result = lin_sin(-PI);
    printf("sine test:\nerror (-pi in): %d / 2147500000\n", abs(result));
    
    result = lin_sin(-PI/2);
    printf("error (-pi/2 in): %d / 2147500000\n", abs(result+(1<<30)));
    
    result = lin_sin(-PI/4);
    printf("error (-pi/4 in): %d / 2147500000\n", abs(result+(1<<29)));
    
    result = lin_sin(0);
    printf("error (0 in): %d / 2147500000\n", abs(result));
    
    result = lin_sin(PI/4);
    printf("error (pi/4 in): %d / 2147500000\n", abs(result-(1<<29)));
    
    result = lin_sin(PI/2);
    printf("error (pi/2 in): %d / 2147500000\n", abs(result-(1<<30)));
    
    result = lin_sin(PI);
    printf("error (pi in): %d / 2147500000\n", abs(result));
}

void cosine_test() {
    int result;
    
    result = lin_cos(-PI);
    printf("cosine test\nerror (-pi in): %d / 2147500000\n", abs(result+(1<<30)));
    
    result = lin_cos(-PI/2);
    printf("error (-pi/2 in): %d / 2147500000\n", abs(result));
    
    result = lin_cos(-PI/4);
    printf("error (-pi/4 in): %d / 2147500000\n", abs(result-(1<<29)));
    
    result = lin_cos(0);
    printf("error (0 in): %d / 2147500000\n", abs(result-(1<<30)));
    
    result = lin_cos(PI/4);
    printf("error (pi/4 in): %d / 2147500000\n", abs(result-(1<<29)));
    
    result = lin_cos(PI/2);
    printf("error (pi/2 in): %d / 2147500000\n", abs(result));
    
    result = lin_cos(PI);
    printf("error (pi in): %d / 2147500000\n", abs(result+(1<<30)));
}

void dot_product_test() {
    double m1[4];
    double m2[4];

    m1[0] = 3.0;
    m1[1] = 5.0;
    m1[2] = 7.0;
    m1[3] = 9.0;

    m2[0] = 8.0;
    m2[1] = 9.0;
    m2[2] = 14.0;
    m2[3] = 15.0;

    assert(dotProduct(m1, m2) == 302);
}

void matmult_test() {
    double** m1 = (double**)malloc(sizeof(double**) * 3);
    double** m2 = (double**)malloc(sizeof(double**) * 3);
    double** m2_t = (double**)malloc(sizeof(double**) * 3);
    double** dest = (double**)malloc(sizeof(double**) * 3);

    initIdentityMatrix(m1);
    initIdentityMatrix(m2);
    initIdentityMatrix(m2_t);
    initIdentityMatrix(dest);


    m1[0][0] = 0.30;
    m1[0][1] = 0.40;
    m1[0][2] = 0.50;
    m1[1][0] = 0.60;
    m1[1][1] = 0.70;
    m1[1][2] = 0.80;
    m1[2][0] = 0.90;
    m1[2][1] = 0.100;
    m1[2][2] = 0.110;

    m2[0][0] = 0.90;
    m2[0][1] = 0.50;
    m2[0][2] = 0.40;
    m2[1][0] = 0.70;
    m2[1][1] = 0.80;
    m2[1][2] = 0.90;
    m2[2][0] = 0.20;
    m2[2][1] = 0.30;
    m2[2][2] = 0.10;

    matmul(m1, m2, dest);
    assert(dest[0][0] == 0.650);
    assert(dest[0][1] == 0.620);
    assert(dest[0][2] == 0.530);
    assert(dest[1][0] == 0.1190);
    assert(dest[1][1] == 0.1100);
    assert(dest[1][2] == 0.950);
    assert(dest[2][0] == 0.1730);
    assert(dest[2][1] == 0.1580);
    assert(dest[2][2] == 0.1370);
}

int main(void) {
    printf("running diagonalize tests...\n");
    
    sine_test();
    cosine_test();
    dot_product_test();

    printf("all tests passed\n");
    return 0;
}
