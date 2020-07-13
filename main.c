#include <diagonalize.h>
#include <linear_approx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// TODO: #define IDENTITY_MATRIX_M

void dot_productM(int16_t m1[M][M], int16_t m2[M][M], int16_t dest[M][M]);
void transposeM(int16_t source[M][M], int16_t dest[M][M]);
void print_matrix2(int16_t matrix[2][2]);
void print_matrixM(int16_t matrix[M][M]);
void print_descaled(int16_t matrix[M][M]);

int main(void) {
    // initialize done flag
    bool done = false;
    // initialize matrices
    int16_t input[M][M] = {
        {31, 77, -11, 26},
        {-42, 14, 79, -53},
        {-68, -10, 45, 90},
        {34, 16, 38, -19}
    };
    /*// scale input matrix
    int mat_M[M][M];
    for (int i=0; i<M; i++) {
        for (int j=0; j<M; j++) {
            mat_M[i][j] = (input[i][j] << SF_ATAN_IN);
        }
    }*/
    //print_descaled(mat_M);
    
    // scaled identity matrices
    int16_t U[M][M], Vt[M][M], I[M][M];
    for (int i=0; i<M; i++) {
        for (int j=0; j<M; j++) {
            if (i != j) {
                I[i][j] = 0;
                U[i][j] = 0;
                Vt[i][j] = 0;
            } else {
                I[i][j] = (1<<SF_ATAN_IN);
                U[i][j] = (1<<SF_ATAN_IN);
                Vt[i][j] = (1<<SF_ATAN_IN);
            }
        }
    }   
    
    // sweeps
    while (!done) {
        // select submatrix indices
        for (int i=0; i<(M-1); i++) {
            for (int j=i+1; j<M; j++) {
                int16_t sum, sumb, diff, diffb, ltheta, rtheta, lcos, lsin, rcos, rsin;
                int16_t r_U[M][M], r_V[M][M], r_Ut[M][M], r_Vt[M][M];           
                //printf("i: %d, j: %d\n", i, j);
                
                // calculate rotation angles
                // TODO: saturating addition?
                sum = mat_M[j][i] + mat_M[i][j];
                sumb = (mat_M[j][j] - mat_M[i][i] + SF_ATAN_IN-1) >> SF_ATAN_IN; 
                if (sum > 0) {
                    if (sumb > 0) {
                        // Q1
                        sum = arctan(sum/sumb);
                    } else if (sumb < 0) {
                        // Q2: angle is pi - arctan(), scaled
                        sum = (1<<SF_ATAN_OUT) - arctan(sum/sumb);
                    } else {
                        // angle is pi/2, scaled
                        sum = 1 << (SF_ATAN_OUT-1);                                             
                    }
                } else if (sum < 0) {
                    if (sumb < 0) {
                        // Q3: angle is arctan() - pi, scaled
                        sum = arctan(sum/sumb) - (1<<SF_ATAN_OUT);
                    } else if (sumb > 0) {
                        // Q4
                        sum = arctan(sum/sumb);
                    } else {
                        // angle is -pi/2, scaled
                        sum = -(1 << (SF_ATAN_OUT-1));                            
                    }
                } else {
                    if (sumb > 0) {
                        // angle is 0
                        sum = 0;
                    } else if (sumb < 0) {
                        // angle is pi, scaled
                        sum = 1 << SF_ATAN_OUT;
                    } else {
                        printf("\nDANGER: input to arctan() is 0/0\n\n");
                        return EXIT_FAILURE;
                    }
                }
                
             /*   sum = input[j][j]-input[i][i];
                if (sum != 0) {
                    sum = (input[j][i]+input[i][j])/sum;
                    printf("arctan input=%d, output=", sum);
                    sum = lin_arctan(sum);
                    printf("%d\n", sum);
                } else {
                    int temp = input[j][i]+input[i][j];
                    if (temp > 0) {
                        // sum equals pi/2, scaled
                        sum = 1 << (SF_ATAN_OUT-1); 
                    } else if (temp != 0) {
                        // sum equals -pi/2, scaled
                        sum = -(1 << (SF_ATAN_OUT-1));    
                    } else {
                        //sum = 0;
                        printf("\nDANGER: input to arctan() is 0/0\n\n");
                        return EXIT_FAILURE;
                    }
                }*/
                
                // TODO: saturating addition?
                diff = mat_M[j][i] - mat_M[i][j];
                diffb = (mat_M[j][j] + mat_M[i][i] + SF_ATAN_IN-1) >> SF_ATAN_IN; 
                if (diff > 0) {
                    if (diffb > 0) {
                        // Q1
                        diff = arctan(diff/diffb);
                    } else if (diffb < 0) {
                        // Q2: angle is pi - arctan(), scaled
                        diff = (1<<SF_ATAN_OUT) - arctan(diff/diffb);
                    } else {
                        // angle is pi/2, scaled
                        diff = 1 << (SF_ATAN_OUT-1);                                             
                    }
                } else if (diff < 0) {
                    if (diffb < 0) {
                        // Q3: angle is arctan() - pi, scaled
                        diff = arctan(diff/diffb) - (1<<SF_ATAN_OUT);
                    } else if (diffb > 0) {
                        // Q4
                        diff = arctan(diff/diffb);
                    } else {
                        // angle is -pi/2, scaled
                        diff = -(1 << (SF_ATAN_OUT-1));                            
                    }
                } else {
                    if (diffb > 0) {
                        // angle is 0
                        diff = 0;
                    } else if (diffb < 0) {
                        // angle is pi, scaled
                        diff = 1 << SF_ATAN_OUT;
                    } else {
                        printf("\nDANGER: input to arctan() is 0/0\n\n");
                        return EXIT_FAILURE;
                    }
                }
                
                /*diff = input[j][j]+input[i][i];
                if (diff != 0) {
                    diff = (input[j][i]-input[i][j])/diff;
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
                        //diff = 0;
                        printf("\nDANGER: input to arctan() is 0/0\n\n");
                        return EXIT_FAILURE;
                    }
                }*/
                
                ltheta = (sum - diff + 1) >> 1;   // TODO: saturating addition?
                rtheta = (sum + diff + 1) >> 1;
                
                printf("sum: %d, diff: %d, ltheta: %d, rtheta: %d\n\n", sum, diff, ltheta, rtheta);
                
                // calculate rotation matrix elements
                lcos = lin_cos(ltheta);
                lsin = lin_sin(ltheta);
                rcos = lin_cos(rtheta);
                rsin = lin_sin(rtheta);
                
                // build rotation matrices
                memcpy(r_U, I, M*M*sizeof(int16_t));
                memcpy(r_Vt, I, M*M*sizeof(int16_t));
                
                r_U[i][i] = lcos;
                r_U[i][j] = -lsin;
                r_U[j][i] = lsin;
                r_U[j][j] = lcos;
                
                r_Vt[i][i] = rcos;
                r_Vt[j][i] = -rsin;
                r_Vt[i][j] = rsin;
                r_Vt[j][j] = rcos;
                
                // apply rotations to M
                dot_productM(r_U, mat_M, mat_M);
                dot_productM(mat_M, r_Vt, mat_M);
                print_descaled(mat_M);
                
                // update U and V
                transposeM(r_U, r_Ut);
                dot_productM(U, r_Ut, U);
                
                transposeM(r_Vt, r_V);
                dot_productM(r_V, Vt, Vt);
            }
        }
        //print_matrixM(mat_M);
        // check if M is close enough
        done = true;
        for (int i=0; i<M; i++) {
            for (int j=0; j<M; j++) {
                if (i != j) {
                    if (mat_M[i][j] != 0) {
                        done = false;
                    }
                }
            }
        }
        return EXIT_SUCCESS; //TODO: remove after testing
    }    
    return EXIT_SUCCESS;
}

void dot_productM(int16_t m1[M][M], int16_t m2[M][M], int16_t dest[M][M]) {
    int16_t temp[M][M];
    
    //print_matrixM(m1);
    //print_matrixM(m2);
    
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            int16_t sum = 0;
            for (int n=0; n<M; n++) {
                sum += (m1[k][n]*m2[n][l]+(1<<(SF_ATAN_IN-1))) >> SF_ATAN_IN; // TODO: saturating addition
            }
            temp[k][l] = sum;
        }
    }        
    
    //print_matrixM(temp);
    
    memcpy(dest, temp, M*M*sizeof(int16_t)); 
    return;
}

void transposeM(int16_t source[M][M], int16_t dest[M][M]) {
    int16_t result[M][M];
    
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            result[k][l] = source[l][k];
        }
    }
    memcpy(dest, result, M*M*sizeof(int16_t));
    return;
}

void print_matrix2(int16_t matrix[2][2]) {
    for (int k=0; k<2; k++) {
        for (int l=0; l<2; l++) {
            printf("%d ", matrix[k][l]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void print_matrixM(int16_t matrix[M][M]) {
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            printf("%d ", matrix[k][l]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void print_descaled(int16_t matrix[M][M]) {
    for (int k=0; k<M; k++) {
        for (int l=0; l<M; l++) {
            printf("%d ", (matrix[k][l] + SF_ATAN_IN-1) >> SF_ATAN_IN);
        }
        printf("\n");
    }
    printf("\n");
    return;
}
