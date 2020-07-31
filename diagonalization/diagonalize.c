#include "diagonalize.h"
#include <linear_approx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// angles are calculated for SF_ATAN_OUT = (2^15)/pi
const int angles[14] = {8192, 4836, 2555, 1297, 651, 326, 163, 81, 41, 20, 10, 5, 3, 1};
//const int16_t angles[6] = {6434, 3798, 2007, 1019, 511, 256};//, 128, 64}; for 2^13

void cordic(int* cos, int* sin, int theta)
{
    // initialize sin/cos vector
    int v[2] = {(1<<SF_ATAN_IN), 0};
    int angle;
    
    for (int j=0; j<ITER; j++) {
        //int factor;
        // initialize temporary variables
        int temp0 = v[0],
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
    *cos = (int)((temp_cos + (1<<16))>>17);
    *sin = (int)((temp_sin + (1<<16))>>17);
    return;
}

void dot_productM(int m1[M][M], int m2[M][M], int dest[M][M])
{
    int temp[M][M];
    
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
            temp[k][l] = (int)((sum + (SF_ATAN_IN-1)) >> SF_ATAN_IN);
        }
    }        
    
    //print_descaled(temp);
    
    memcpy(dest, temp, M*M*sizeof(int)); 
    return;
}

void transposeM(int source[M][M], int dest[M][M])
{
    int result[M][M];
    
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            result[k][l] = source[l][k];
        }
    }
    memcpy(dest, result, M*M*sizeof(int));
    return;
}

void print_matrix2(int matrix[2][2])
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

void print_matrixM(int matrix[M][M])
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

void print_descaled(int matrix[M][M])
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
