#include <arctan.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define M 6

typedef struct svd {
    int** U;
    int** S;
    int** V;
} SVD;

void initIdentityMatrix(int** matrix) {
    for (int i = 0; i < M; ++i) {
        matrix[i] = (int*)malloc(sizeof(int*) * M);
    }
    int value;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == j) {
                value = 1;
            } else {
                value = 0;
            }
            matrix[i][j] = value;
        }
    }
}

SVD diagonalize(int** matrix) {
    SVD svd;
    
    int** U = (int**)malloc(sizeof(int**) * M);
    int** S = matrix;
    int** V = (int**)malloc(sizeof(int**) * M);

    // stubbed out: initialize U, S, and V to zero matrices
    // TODO: implement Jacobi method to find values for U, S, and V
    initIdentityMatrix(U);

    initIdentityMatrix(V);

    svd.U = U;
    svd.S = S;
    svd.V = V;

    return svd;
}

void printout(const char * matrixName, int** matrix) {
    printf("----------------------------------\n");
    printf("%s:\n", matrixName);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int max_val = pow(2, N_BITS);
    int** matrix;
    for (int i = 0; i < M; ++i) {
        matrix[i] = (int*)malloc(sizeof(int*) * M);
    }
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            matrix[i][j] = rand() % max_val;
        }
    }

    SVD svd = diagonalize(matrix);
    printout("U", svd.U);
    printout("S", svd.S);
    printout("V", svd.V);

    return 0;
}