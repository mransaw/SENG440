#include <diagonalize.h>
#include <linear_approx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define ITER 6
#define KN 79595
// TODO: #define IDENTITY_MATRIX_M

// angles are calculated for SF_ATAN_OUT = (2^13)/pi
static const int16_t angles[6] = {6434, 3798, 2007, 1019, 511, 256};//, 128, 64};

void cordic(int16_t* cos, int16_t* sin, int16_t angle);
void dot_productM(int16_t m1[M][M], int16_t m2[M][M], int16_t dest[M][M]);
void transposeM(int16_t source[M][M], int16_t dest[M][M]);
void print_matrix2(int16_t matrix[2][2]);
void print_matrixM(int16_t matrix[M][M]);
void print_descaled(int16_t matrix[M][M]);

int main(void)
{
    // clock variables for benchmarking
    clock_t clk, clk_total,
            clk_rota=0,
            clk_angles=0;
    
    // initialize done flag
    bool done = false;
    
    // initialize matrices
    int16_t mat_M[M][M] = {
        {31, 77, -11, 26},
        {-42, 14, 79, -53},
        {-68, -10, 45, 90},
        {34, 16, 38, -19}
    };
    
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
    
    // count number of sweeps
    int sweeps = 0;
    
    // start timer for SVD algorithm
    clk_total = clock();
    
    while (!done) {
        // select submatrix indices
        for (int i=0; i<(M-1); i++) {
            for (int j=i+1; j<M; j++) {
                //int sum, sumb, diff, diffb, ltheta, rtheta;
                int16_t sum, sumb, diff, diffb, ltheta, rtheta, lcos, lsin, rcos, rsin;
                int16_t r_U[M][M], r_V[M][M], r_Ut[M][M], r_Vt[M][M];     
                
                double theta_sum, theta_diff, dltheta, drtheta;
                      
                //printf("i: %d, j: %d\n", i, j);
                
                // calculate rotation angles
                // TODO: saturating addition?
                
                // start timer for rotation angle calculations
                clk = clock();
                
                sum = mat_M[j][i] + mat_M[i][j];
                sumb = mat_M[j][j] - mat_M[i][i];
                //printf("sum=%f, sumb=%f\n", (double)sum, (double)sumb);
                if (sumb != 0) {
                    theta_sum = atan((double)sum/sumb);
                    //printf("arctan output=");
                    //sum = lin_arctan(sum);
                    sum = (int16_t)(theta_sum * pow(2,SF_ATAN_OUT)/M_PI);
                    //printf("%f, scaled: %d\n", theta_sum, sum);
                } else {
                    if (sum > 0) {
                        // sum equals pi/2, scaled
                        sum = 1 << (SF_ATAN_OUT-1); 
                    } else if (sum < 0) {
                        // sum equals -pi/2, scaled
                        sum = -(1 << (SF_ATAN_OUT-1));    
                    } else {
                        printf("\nDANGER: input to arctan() is 0/0\n\n");
                        return EXIT_FAILURE;
                    }
                }
                
                // TODO: saturating addition?
              
                diff = mat_M[j][i] - mat_M[i][j];
                diffb = mat_M[j][j] + mat_M[i][i];
                if (diffb != 0) {
                    /*diff = (mat_M[j][i]-mat_M[i][j])/diff;
                    printf("arctan input=%d, output=", diff);
                    diff = lin_arctan(diff);
                    printf("%d\n\n", diff);*/
                    
                    theta_diff = atan((double)diff/diffb);
                    //theta_diff = atan2((double)diff,(double)diffb);
                    //printf("arctan output=");
                    //sum = lin_arctan(sum);
                    diff = (int16_t)(theta_diff * pow(2,SF_ATAN_OUT)/M_PI);
                    //printf("%f, scaled: %d\n", theta_diff, diff);
                } else {
                    if (diff > 0) {
                        // diff equals pi/2, scaled
                        diff = 1 << (SF_ATAN_OUT-1);   
                    } else if (diff < 0) {
                        // diff equals -pi/2, scaled
                        diff = -(1 << (SF_ATAN_OUT-1));   
                    } else {
                        printf("\nDANGER: input to arctan() is 0/0\n\n");
                        printf("%d sweeps\n", sweeps);
                        return EXIT_FAILURE;
                    }
                }
                
                //ltheta = (sum - diff + 1) >> 1;   // TODO: saturating addition?
                //rtheta = (sum + diff + 1) >> 1;
                
                dltheta = (theta_sum - theta_diff) / 2;
                drtheta = (theta_sum + theta_diff) / 2;
                
                //printf("sum: %d, diff: %d, ltheta: %d, rtheta: %d\n", sum, diff, ltheta, rtheta);
                //printf("sum: %d, diff: %d, ltheta: %f, rtheta: %f\n", sum, diff, dltheta, drtheta);
                
                // calculate rotation matrix elements
               /* lcos = lin_cos(ltheta);
                lsin = lin_sin(ltheta);
                rcos = lin_cos(rtheta);
                rsin = lin_sin(rtheta);*/
                

                cordic(&lcos, &lsin, (int16_t)(dltheta*pow(2,SF_ATAN_IN)));
                
                cordic(&rcos, &rsin, (int16_t)(drtheta*pow(2,SF_ATAN_IN)));
                
                clk = clock() - clk;
                clk_angles += clk;
                printf("calculating rotation angles took %.0f [us]\n", 1000000*(double)clk/(CLOCKS_PER_SEC));

                //printf("lcos: %f, lsin: %f, rcos: %f, rsin: %f\n\n",(double)lcos/pow(2,SF_ATAN_IN),(double)lsin/pow(2,SF_ATAN_IN),(double)rcos/pow(2,SF_ATAN_IN),(double)rsin/pow(2,SF_ATAN_IN));
                
                /*lcos = (int16_t)(cos(dltheta)*pow(2,SF_ATAN_IN));
                lsin = (int16_t)(sin(dltheta)*pow(2,SF_ATAN_IN));
                rcos = (int16_t)(cos(drtheta)*pow(2,SF_ATAN_IN));
                rsin = (int16_t)(sin(drtheta)*pow(2,SF_ATAN_IN));
                
                printf("lcos: %f, lsin: %f, rcos: %f, rsin: %f\n\n",(double)lcos/pow(2,SF_ATAN_IN),(double)lsin/pow(2,SF_ATAN_IN),(double)rcos/pow(2,SF_ATAN_IN),(double)rsin/pow(2,SF_ATAN_IN));*/
                
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
                
                // start timer for matrix rotations and updating MUV
                clk = clock();
                
                // apply rotations to M
                dot_productM(r_U, mat_M, mat_M);
                dot_productM(mat_M, r_Vt, mat_M);
                
                // update U and V
                transposeM(r_U, r_Ut);
                dot_productM(U, r_Ut, U);

                //print_descaled(U);
                
                transposeM(r_Vt, r_V);
                dot_productM(r_V, Vt, Vt);
                
                clk = clock() - clk;
                clk_rota += clk;
                printf("rotating M and updating MUV took %.0f [us]\n\n", (double)1000000*(double)clk/(CLOCKS_PER_SEC));
                
                //transposeM(Vt, r_V);
                //print_descaled(r_V);
                
                //print_matrixM(mat_M);
                //return -1;
            }
        }
        print_matrixM(mat_M);
        // check if M is close enough
        done = true;
        for (int i=0; i<M; i++) {
            for (int j=0; j<M; j++) {
                if (i != j) {
                    // TODO: determine what the maximum residual should be
                    if (abs(mat_M[i][j]) > 8) {
                        done = false;
                    }
                }
            }
        }
        //return -1; //TODO: remove after testing
        sweeps++;
    }
    clk_total = clock() - clk_total;
    printf("%d sweeps, took %.0f microseconds total\ncalculating angles took %.0fus (%.0f avg), rotating M and updating MUV took %.0fus (%.0f avg)\n\n", sweeps, 1000000*(double)clk_total/(CLOCKS_PER_SEC), 1000000*(double)clk_angles/(CLOCKS_PER_SEC), 1000000*(double)clk_angles/(CLOCKS_PER_SEC*6*sweeps), 1000000*(double)clk_rota/(CLOCKS_PER_SEC), 1000000*(double)clk_rota/(CLOCKS_PER_SEC*6*sweeps));
    print_matrixM(mat_M);
    return EXIT_SUCCESS;
}

void cordic(int16_t* cos, int16_t* sin, int16_t theta)
{
    // initialize sin/cos vector
    int16_t v[2] = {(1<<SF_ATAN_IN), 0};
    int16_t angle;
    
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

void dot_productM(int16_t m1[M][M], int16_t m2[M][M], int16_t dest[M][M])
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
