#include <arctan.h>
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

void matmul(int** m1, int** m2, int** dest) {
    // apply matrix multiplication m1 x m2, and store the resulting matrix in dest
}

void applyRotations(SVD svd, int i, int j, int theta_l, int theta_r) {
    int cos_l = cos(theta_l);
    int sin_l = sin(theta_l);
    int cos_r = cos(theta_r);
    int sin_r = sin(theta_r);

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

    int** _U_t = transpose(_U);
    int** _V_t = transpose(_V);
    int** V_t = transpose(svd.V);


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