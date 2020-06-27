#include <linear_approx.h>
#include <assert.h>
#include <stdio.h>
#include <diagonalize.h>
#include <stdlib.h>
void arctan_test() {
    int X = 1030;
    int theta = arctan(X);
    assert(theta == (1319*X+291));
}

void cosine_test() {
    int X = 1030;
    int theta = lin_cos(X);
    assert(theta == (1319*X+291));
}

void dot_product_test() {
    double* m1 = (double*)malloc(sizeof(double*) * 2);
    double* m2 = (double*)malloc(sizeof(double*) * 2);

    m1[0] = 3.0;
    m1[1] = 5.0;
    m1[2] = 7.0;

    m2[0] = 8.0;
    m2[1] = 9.0;
    m2[2] = 14.0;

    assert(dotProduct(m1, m2) == 167);
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
    dot_product_test();
    //matmult_test();
    printf("all tests passed\n");
    return 0;
}