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

void initMatrix(int** matrix) {
    for (int i = 0; i < M; ++i) {
        matrix[i] = (int*)malloc(sizeof(int*) * M);
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            matrix[i][j] = 0;
        }
    }
}

SVD diagonalize(int matrix[M][M]) {
    SVD svd;
    
    int** U = (int**)malloc(sizeof(int**) * M);
    int** S = (int**)malloc(sizeof(int**) * M);
    int** V = (int**)malloc(sizeof(int**) * M);

    // stubbed out: initialize U, S, and V to zero matrices
    // TODO: implement Jacobi method to find values for U, S, and V
    initMatrix(U);
    initMatrix(S);
    initMatrix(V);

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
    int matrix[M][M];
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