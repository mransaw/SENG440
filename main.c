#include <diagonalize.h>
#include <linear_approx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SF_ATAN_IN 14
#define SF_SINCOS_OUT 14

// TODO: #define IDENTITY_MATRIX_M

void dot_productM(int m1[M][M], int m2[M][M], int dest[M][M]);
void transposeM(int source[M][M], int dest[M][M]);
void print_matrix2(int matrix[2][2]);
void print_matrixM(int matrix[M][M]);

int main(void) {
    // initialize done flag
    bool done = false;
    // initialize matrices
    int input[M][M] = {
        {31, 77, -11, 26},
        {-42, 14, 79, -53},
        {-68, -10, 45, 90},
        {34, 16, 38, -19}
    };
    // identity matrices
    int U[M][M], Vt[M][M], I[M][M];
    for (int i=0; i<M; i++) {
        for (int j=0; j<M; j++) {
            if (i != j) {
                I[i][j] = 0;
                U[i][j] = 0;
                Vt[i][j] = 0;
            } else {
                I[i][j] = (1<<SF_SINCOS_OUT);
                U[i][j] = 1;
                Vt[i][j] = 1;
            }
        }
    }   
    
    // sweeps
    while (!done) {
        // select submatrix indices
        for (int i=0; i<(M-1); i++) {
            for (int j=i+1; j<M; j++) {
                int sum, diff, ltheta, rtheta, lcos, lsin, rcos, rsin;
                int r_U[M][M], r_V[M][M], r_Ut[M][M], r_Vt[M][M];           
                //printf("i: %d, j: %d\n", i, j);
                
                // calculate rotation angles
                sum = input[j][j]-input[i][i];
                if (sum != 0) {
                    sum = ((input[j][i]+input[i][j])<<SF_ATAN_IN)/sum;
                    printf("arctan input=%d, output=", sum);
                    sum = lin_arctan(sum);
                    printf("%d\n", sum);
                } else {
                    int temp = input[j][i]+input[i][j];
                    if (temp > 0) {
                        // TODO: sum equals pi/2, scaled
                    } else if (temp != 0) {
                        // TODO: sum equals -pi/2, scaled
                    } else {
                        sum = 0;
                        printf("\nDANGER\n\n");
                    }
                }
                
                diff = input[j][j]+input[i][i];
                if (diff != 0) {
                    diff = ((input[j][i]-input[i][j])<<SF_ATAN_IN)/diff;
                    printf("arctan input=%d, output=", diff);
                    diff = lin_arctan(diff);
                    printf("%d\n\n", diff);
                } else {
                    int temp = input[j][i]-input[i][j];
                    if (temp > 0) {
                        // TODO: diff equals pi/2, scaled
                    } else if (temp != 0) {
                        // TODO: diff equals -pi/2, scaled
                    } else {
                        diff = 0;
                        printf("\nDANGER\n\n");
                    }
                }
                
                ltheta = (sum - diff + 1)>>1;   // TODO: saturating addition?
                rtheta = (sum + diff + 1)>>1;
                
                //printf("sum: %d, diff: %d, ltheta: %d, rtheta: %d\n", sum, diff, ltheta, rtheta);
                
                // calculate rotation matrix elements
                lcos = lin_cos(ltheta);
                lsin = lin_sin(ltheta);
                rcos = lin_cos(rtheta);
                rsin = lin_sin(rtheta);
                
                // build rotation matrices
                memcpy(r_U, I, M*M*sizeof(int));
                memcpy(r_V, I, M*M*sizeof(int));
                
                r_U[i][i] = lcos;
                r_U[i][j] = -lsin;
                r_U[j][i] = lsin;
                r_U[j][j] = lcos;
                
                r_Vt[i][i] = rcos;
                r_Vt[j][i] = -rsin;
                r_Vt[i][j] = rsin;
                r_Vt[j][j] = rcos;
                
                // apply rotations to M
                dot_productM(r_U, input, input);
                dot_productM(input, r_Vt, input);
                //print_matrixM(input);
                
                // update U and V
                transposeM(r_U, r_Ut);
                dot_productM(U, r_Ut, U);
                
                transposeM(r_Vt, r_V);
                dot_productM(r_V, Vt, Vt);
            }
        }
        // check if M is close enough
        done = true;
        for (int i=0; i<M; i++) {
            for (int j=0; j<M; j++) {
                if (i != j) {
                    if (input[i][j] != 0) {
                        done = false;
                    }
                }
            }
        }
    }    
    return EXIT_SUCCESS;
}

void dot_productM(int m1[M][M], int m2[M][M], int dest[M][M]) {
    int temp[M][M];
    
    print_matrixM(m1);
    print_matrixM(m2);
    
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            int sum = 0;
            for (int n=0; n<M; n++) {
                sum += (m1[k][n]*m2[n][l]+(1<<14))>>15; // TODO: saturating addition
            }
            temp[k][l] = sum;
        }
    }        
    
    print_matrixM(temp);
    
    memcpy(dest, temp, M*M*sizeof(int)); 
    return;
}

void transposeM(int source[M][M], int dest[M][M]) {
    int result[M][M];
    
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            result[k][l] = source[l][k];
        }
    }
    memcpy(dest, result, M*M*sizeof(int));
    return;
}

void print_matrix2(int matrix[2][2]) {
    for (int k=0; k<2; k++) {
        for (int l=0; l<2; l++) {
            printf("%d ", matrix[k][l]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void print_matrixM(int matrix[M][M]) {
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            printf("%d ", matrix[k][l]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}
