#include "diagonalize.h"
#include <linear_approx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// angles are calculated for SF_ATAN_OUT = (2^15)/pi
const int angles[14] = {8192, 4836, 2555, 1297, 651, 326, 163, 81, 41, 20, 10, 5, 3, 1};
//const int16_t angles[6] = {6434, 3798, 2007, 1019, 511, 256};//, 128, 64}; for 2^13

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
/*
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

        int fixed_point = 1 << (N_BITS - 1);
        X_sum = X_sum * fixed_point;

        double theta_sum = arctan(X_sum);
        theta_sum = ((double)theta_sum) / ((double)(fixed_point));

        X_diff = X_diff * fixed_point;
        double theta_diff = arctan(X_diff);
        theta_diff = ((double)theta_diff) / ((double)(fixed_point));

        printf("atan(X_sum) = %f\n", atan(X_sum));
        printf("arctan(int_theta_sum) = theta_sum = %f\n", theta_sum);
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
        printf("SWEEP %d", row + 1);
        for (col = row + 1; col < M; ++col) {
            printf(", ITERATION %d\n", col);
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
}*/

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


void cordic(int16_t* cos, int16_t* sin, int theta)
{
    // initialize sin/cos vector
    int16_t v[2] = {(1<<SF_ATAN_IN), 0};
    int angle;
    
    for (int j=0; j<ITER; j++) {
        //int factor;
        // initialize temporary variables
        int16_t temp0 = v[0],
                temp1 = v[1];
                
        // perform rotation
        angle = angles[j];
        if (theta < 0) {
            //factor = -(1 >> shiftf);
            
            v[0] += (temp1 >> j);
            v[1] -= (temp0 >> j);
            theta += angle;
        } else {
            //factor = (1 >> shiftf);
            
            v[0] -= (temp1 >> j);
            v[1] += (temp0 >> j);
            theta -= angle;
        }
        
        //shiftf++;
        //v[0] = v[0] - factor*v[1];
        //v[1] = factor*temp + v[1];
        
        /*if ((j+1) > ANGLES_LENGTH) {
            angle = (angle+1) >> 1;
        } else {
            angle = angles(j+1);
        }*/
    }
    
    /*double A = 1;
    for (int i=0; i<ITER; i++) {
        A *= sqrt(1 + pow(2,-2*i));
    }
    
    double Kn = 1/A;*/
    
    //printf("A: %f, Kn: %f\n", A, Kn);`
    
    // apply output factor Kn
    int temp_cos = v[0] * KN;
    int temp_sin = v[1] * KN;
    
    //printf("input: %d, cos: %d, sin: %d\n", theta, v[0], v[1]); 
    // remove added SF (from Kn) and return results
    *cos = (int16_t)((temp_cos + (1<<16))>>17);
    *sin = (int16_t)((temp_sin + (1<<16))>>17);
    return;
}

void dot_productM(int16_t m1[restrict M][M], int16_t m2[restrict M][M], int16_t dest[M][M])
{
    int16_t temp[M][M];
    
    //print_descaled(m1);
    //print_descaled(m2);
    
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            int sum = 0;
            for (int n=0; n<M; n++) {
                sum += m1[k][n]*m2[n][l]; // TODO: saturating addition?
              // printf("1[%d][%d] * 2[%d][%d]\n",k,n,n,l);
               // printf("sum=%d\n\n, ", sum);
            }
            //printf("temp: %d, ",((sum + (SF_ATAN_IN-1)) >> SF_ATAN_IN));
            temp[k][l] = (int16_t)((sum + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
        }
    }        
    
    //print_descaled(temp);
    
    memcpy(dest, temp, M*M*sizeof(int16_t)); 
    return;
}

void transposeM(int16_t source[restrict M][M], int16_t dest[M][M])
{
    int16_t result[M][M];
    
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            result[k][l] = source[l][k];
        }
    }
    memcpy(dest, result, M*M*sizeof(int16_t));
    return;
}

void print_matrix2(int16_t matrix[2][2])
{
    for (int k=0; k<2; k++) {
        for (int l=0; l<2; l++) {
            printf("%d ", matrix[k][l]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void print_matrixM(int16_t matrix[M][M])
{
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            printf("%d ", matrix[k][l]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void print_descaled(int16_t matrix[M][M])
{
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            printf("%f ", (double)matrix[k][l]/pow(2,SF_ATAN_IN));
        }
        printf("\n");
    }
    printf("\n");
    return;
}
