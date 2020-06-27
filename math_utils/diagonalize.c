#include "linear_approx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define M 6

typedef struct svd_struct {
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

int dotProduct(int* v1, int* v2) {
    int sum = 0;
    for (int i = 0; i < M; ++i) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

void transpose(int** source, int** dest) {
    for (int row = 0; row < M; ++row) {
        for (int col = 0; col < M; ++col) {
            dest[row][col] = source[col][row];
        }
    }
}

void matmul(int** m1, int** m2, int** dest) {
    int** m2_t = (int**)malloc(sizeof(int**));
    transpose(m2, m2_t);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            dest[i][j] = dotProduct(m1[i], m2_t[j]);
        }
    }
}

void applyRotations(SVD svd, int i, int j, int theta_l, int theta_r) {
    int cos_l = lin_cos(theta_l);
    int sin_l = lin_sin(theta_l);
    int cos_r = lin_cos(theta_r);
    int sin_r = lin_sin(theta_r);

    int** _U = (int**)malloc(sizeof(int**) * M);
    int** _V = (int**)malloc(sizeof(int**) * M);
    initIdentityMatrix(_U);
    initIdentityMatrix(_V);

    _U[i][i] = cos_l;
    _U[j][j] = cos_l;
    _U[j][i] = sin_l;
    _U[i][j] = -1 * sin_l;

    _V[i][i] = cos_r;
    _V[j][j] = cos_r;
    _V[j][i] = -1 * sin_r;
    _V[i][j] = cos_r;

    int** _U_t = (int**)malloc(sizeof(int**) * M);
    transpose(_U, _U_t);
    int** _V_t = (int**)malloc(sizeof(int**) * M);
    transpose(_V, _V_t);
    int** V_t = (int**)malloc(sizeof(int**) * M);
    transpose(svd.V, V_t);


    int** U = (int**)malloc(sizeof(int**) * M);
    int** S = (int**)malloc(sizeof(int**) * M);
    int** S_ = (int**)malloc(sizeof(int**) * M);
    int** V = (int**)malloc(sizeof(int**) * M);
    
    matmul(svd.U, _U_t, U);

    matmul(_U, svd.S, S_);
    matmul(S_, _V_t, S);

    matmul(_V, V_t, V);

    svd.U = U;
    svd.S = S;
    svd.V = V;
}

void applyJacobiMethod(SVD svd, int i, int j) {
        int m_ji = svd.S[j][i];
        int m_ij = svd.S[i][j];
        int m_ii = svd.S[i][i];
        int m_jj = svd.S[j][j];

        int X_sum = (m_ji + m_ij)/(m_jj - m_ii);
        int X_diff = (m_ji - m_ji)/(m_jj + m_ii);

        int theta_sum = arctan(X_sum);
        int theta_diff = arctan(X_diff);
        int theta_r = theta_sum + theta_diff;
        int theta_l = theta_sum - theta_r;

        applyRotations(svd, i, j, theta_l, theta_r);
}

void sweep(int row, int col, SVD svd) {
    int** S = svd.S;
    if (col == M) {
        return;
    } else {
        applyJacobiMethod(svd, row, col);
        sweep(++row, ++col, svd);
    }
}

void startSweeps(SVD svd) {
    sweep(0, 1, svd);
}

SVD diagonalize(int** matrix) {
    SVD svd;
    
    int** U = (int**)malloc(sizeof(int**) * M);
    int** S = matrix;
    int** V = (int**)malloc(sizeof(int**) * M);

    initIdentityMatrix(U);
    initIdentityMatrix(V);

    svd.U = U;
    svd.S = S;
    svd.V = V;

    startSweeps(svd);

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