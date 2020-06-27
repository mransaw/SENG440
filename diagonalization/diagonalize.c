#include "diagonalize.h"
#include <linear_approx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void initIdentityMatrix(double** matrix) {
    for (int i = 0; i < M; ++i) {
        matrix[i] = (double*)malloc(sizeof(double*) * M);
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

double dotProduct(double* v1, double* v2) {
    double sum = 0;
    for (int i = 0; i < M; ++i) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

void transpose(double** source, double** dest) {
    for (int row = 0; row < M; ++row) {
        for (int col = 0; col < M; ++col) {
            dest[row][col] = source[col][row];
        }
    }
}

void matmul(double** m1, double** m2, double** dest) {
    double** m2_t = (double**)malloc(sizeof(double**) * M);
    initIdentityMatrix(m2_t);
    transpose(m2, m2_t);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            dest[i][j] = dotProduct(m1[i], m2_t[j]);
        }
    }
}

void applyRotations(SVD svd, int i, int j, double theta_l, double theta_r) {
    double cos_l = cos(theta_l); //lin_cos(theta_l);
    double sin_l = sin(theta_l); //lin_sin(theta_l);
    double cos_r = cos(theta_r); //lin_cos(theta_r);
    double sin_r = sin(theta_r); //lin_sin(theta_r);

    printf("\ncos_l: %f       cos_r: %f\n", cos_l, cos_r);
    printf("sin_l: %f       sin_r: %f\n", sin_l, sin_r);

    double** i_U = (double**)malloc(sizeof(double**) * M);
    double** i_V = (double**)malloc(sizeof(double**) * M);
    initIdentityMatrix(i_U);
    initIdentityMatrix(i_V);

    i_U[i][i] = cos_l;
    i_U[i][j] = -1 * sin_l;
    i_U[j][i] = sin_l;
    i_U[j][j] = cos_l;

    i_V[i][i] = cos_r;
    i_V[i][j] = -1 * sin_r;
    i_V[j][i] = sin_r;
    i_V[j][j] = cos_r;

    double** i_U_t = (double**)malloc(sizeof(double**) * M);
    initIdentityMatrix(i_U_t);
    transpose(i_U, i_U_t);

    double** i_V_t = (double**)malloc(sizeof(double**) * M);
    initIdentityMatrix(i_V_t);
    transpose(i_V, i_V_t);

    double** V_t = (double**)malloc(sizeof(double**) * M);
    initIdentityMatrix(V_t);
    transpose(*svd.V, V_t);

    matmul(*svd.U, i_U_t, *svd.U); // U' = U * i_U_t

    double** M_i_V_t = (double**)malloc(sizeof(double**) * M);
    initIdentityMatrix(M_i_V_t);

    matmul(*svd.S, i_V_t, M_i_V_t);
    matmul(i_U, M_i_V_t, *svd.S); // = M' = i_U * M * i_V_t

    double** V__T = (double**)malloc(sizeof(double**) * M);
    initIdentityMatrix(V__T);

    matmul(i_V, V_t, V__T); // V'_t = i_V * V_t
    transpose(V__T, *svd.V); // V' = transpose(V'_t)
    printoutSVD(svd);
}

void applyJacobiMethod(SVD svd, int i, int j) {
        int m_ii = (*svd.S)[i][i];
        int m_ji = (*svd.S)[j][i];
        int m_ij = (*svd.S)[i][j];
        int m_jj = (*svd.S)[j][j];

        printf("Jacobi input:\n    %d  %d\n    %d  %d\n", m_ii, m_ij, m_ji, m_jj);

        double X_sum = ((double)(m_ji + m_ij))/((double)(m_jj - m_ii));
        double X_diff = ((double)(m_ji - m_ij))/((double)(m_jj + m_ii));

        printf("X_sum = %f\n", X_sum);
        printf("X_diff = %f\n", X_diff);

        double theta_sum = atan(X_sum); //arctan(X_sum);
        double theta_diff = atan(X_diff); //arctan(X_diff);

        printf("theta_sum = %f\n", theta_sum);
        printf("theta_diff = %f\n", theta_diff);

        double theta_r = 0.5*(theta_sum + theta_diff);
        double theta_l = theta_sum - theta_r;

        printf("theta_l = %f\n", theta_l);
        printf("theta_r = %f\n", theta_r);
        applyRotations(svd, i, j, theta_l, theta_r);
}

void sweep(SVD svd) {
    int row = 0;
    int col = row + 1;
    for (row = 0; row < M; ++row) {
        for (col = row + 1; col < M; ++col) {
            applyJacobiMethod(svd, row, col);
        }
    }
}

SVD diagonalize(double** matrix) {
    SVD svd;
    
    double** U = (double**)malloc(sizeof(double**) * M);
    double** S = matrix;
    double** V = (double**)malloc(sizeof(double**) * M);

    initIdentityMatrix(U);
    initIdentityMatrix(V);

    svd.U = &U;
    svd.S = &S;
    svd.V = &V;
    
    for (int i = 0; i < NUM_SWEEPS; ++i) {
        sweep(svd);
    }

    return svd;
}

void printout(const char * matrixName, double** matrix) {
    printf("----------------------------------\n");
    printf("%s:\n", matrixName);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printoutSVD(const SVD svd) {
    printf("=============================\n");
    printout("U", *svd.U);
    printout("S", *svd.S);
    printout("V", *svd.V);
    printf("=============================\n");
}