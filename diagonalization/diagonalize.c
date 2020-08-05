#include "diagonalize.h"
#include <linear_approx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// angles are calculated for SF_ATAN_OUT = (2^15)/pi
const int angles[10] = {8192, 4836, 2555, 1297, 651, 326, 163, 81, 41};

void cordic(int* cos, int* sin, int theta)
{
    // initialize sin/cos vector
    register int v0 = (1<<SF_ATAN_IN),
                 v1 = 0;
    register int angle;
    
    for (int j=0; j<ITER; j++) {
        // initialize temporary variables
        register int temp0 = v0,
                     temp1 = v1;
                
        // perform rotation
        angle = angles[j];
        if (theta < 0) {
            v0 += (temp1 >> j);
            v1 -= (temp0 >> j);
            theta += angle;
        } else {
            v0 -= (temp1 >> j);
            v1 += (temp0 >> j);
            theta -= angle;
        }
    }
    
    // apply output factor Kn
    v0 *= KN;
    v1 *= KN;
    
    // remove added SF (from Kn) and return results
    *cos = (v0 + (1<<16)) >> 17;
    *sin = (v1 + (1<<16)) >> 17;
    return;
}

void dot_productM(int16_t m1[M][M], int16_t m2[M][M], int16_t dest[M][M])
{
    int16_t temp[M][M];

    for (int l=0; l<M; l++) {

        for (int k=0; k<M; k+=3) { 
             register int sum0 = 0,
                          sum1 = 0,
                          sum2 = 0;
                     
            for (int n=0; n<M; n+=3) {
                sum0 += m1[k][n]*m2[n][l] + m1[k][n+1]*m2[n+1][l] + m1[k][n+2]*m2[n+2][l];
                sum1 += m1[k+1][n]*m2[n][l] + m1[k+1][n+1]*m2[n+1][l] + m1[k+1][n+2]*m2[n+2][l];
                sum2 += m1[k+2][n]*m2[n][l] + m1[k+2][n+1]*m2[n+1][l] + m1[k+2][n+2]*m2[n+2][l];
            }
            
            temp[k][l] = (int16_t)((sum0 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
            temp[k+1][l] = (int16_t)((sum1 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
            temp[k+2][l] = (int16_t)((sum2 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
        }
    }        
    
    //print_descaled(temp);
    
    memcpy(dest, temp, M*M*sizeof(int16_t)); 
    return;
}

void T1dot_productM(int16_t m1[M][M], int16_t m2[M][M], int16_t dest[M][M])
{
    int16_t temp[M][M];
    //memset(temp, 0, M*M*sizeof(int16_t));
    
    //print_matrixM(temp);
    //print_descaled(m2);
    for (int l=0; l<M; l++) {

        for (int k=0; k<M; k++) { 
             register int sum0 = 0;
                     
            for (int n=0; n<M; n+=3) {
                sum0 += m1[n][k]*m2[n][l] + m1[n+1][k]*m2[n+1][l] + m1[n+2][k]*m2[n+2][l];
            }
            
            temp[k][l] = (int16_t)((sum0 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
        }
    }        
    
    //print_descaled(temp);
    
    memcpy(dest, temp, M*M*sizeof(int16_t)); 
    return;
}

void T2dot_productM(int16_t m1[M][M], int16_t m2[M][M], int16_t dest[M][M])
{
     int16_t temp[M][M];
    //memset(temp, 0, M*M*sizeof(int16_t));
    
    //print_matrixM(temp);
    //print_descaled(m2);
    for (int l=0; l<M; l+=3) {

        for (int k=0; k<M; k+=3) { 
             register int sum0 = 0,
                          sum1 = 0,
                          sum2 = 0,
                          sum3 = 0,
                          sum4 = 0,
                          sum5 = 0,
                          sum6 = 0,
                          sum7 = 0,
                          sum8 = 0;
                     
            for (int n=0; n<M; n++) {
                sum0 += m1[k][n]*m2[l][n];
                sum1 += m1[k+1][n]*m2[l][n];
                sum2 += m1[k+2][n]*m2[l][n];
                sum3 += m1[k][n]*m2[l+1][n];
                sum4 += m1[k+1][n]*m2[l+1][n];
                sum5 += m1[k+2][n]*m2[l+1][n];
                sum6 += m1[k][n]*m2[l+2][n];
                sum7 += m1[k+1][n]*m2[l+2][n];
                sum8 += m1[k+2][n]*m2[l+2][n];
            }
            
            temp[k][l] = (int16_t)((sum0 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
            temp[k+1][l] = (int16_t)((sum1 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
            temp[k+2][l] = (int16_t)((sum2 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
            temp[k][l+1] = (int16_t)((sum3 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
            temp[k+1][l+1] = (int16_t)((sum4 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
            temp[k+2][l+1] = (int16_t)((sum5 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
            temp[k][l+2] = (int16_t)((sum6 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
            temp[k+1][l+2] = (int16_t)((sum7 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
            temp[k+2][l+2] = (int16_t)((sum8 + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
        }
    }        
    
    //print_descaled(temp);
    
    memcpy(dest, temp, M*M*sizeof(int16_t)); 
    return;
}

void transposeM(int16_t source[M][M], int16_t dest[M][M])
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
