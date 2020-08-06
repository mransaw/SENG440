#include <diagonalize.h>
#include <linear_approx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

int main(void)
{
    // clock variables for benchmarking
    clock_t clk, clk_total,
            clk_rota=0,
            clk_angles=0;
    
    // initialize matrices
    /*int16_t mat_M[M][M] = {
        {31, 77, -11, 26},
        {-42, 14, 79, -53},
        {-68, -10, 45, 90},
        {34, 16, 38, -19}
    };
    int16_t mat_M[M][M] = {
        {(1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN)},
        {(1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN)},
        {(1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN)},
        {(1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN)},
        {(1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN)},
        {(1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN), (1<<SF_ATAN_IN)}
    };*/
    
    int16_t mat_M[M][M];
    srand(time(0));
    for (int i=0; i<M; i++) {
        for (int j=0; j<M; j++) {
            mat_M[i][j] = (int16_t)(rand() % 0xFFFF);
        }
    }
    
    print_matrixM(mat_M);
    
    // scaled identity matrices
    int16_t U[M][M], Vt[M][M], I[M][M];
    for (int i=0; i<M; i++) {
        for (int j=0; j<M; j++) {
            if (i != j) {
                I[i][j] = 0;
            } else {
                I[i][j] = (1<<SF_ATAN_IN);
            }
        }
    }   
    memcpy(U, I, M*M*sizeof(int16_t));
    memcpy(Vt, I, M*M*sizeof(int16_t));
    
    // count number of sweeps
    int sweeps = 0;
    
    // start timer for SVD algorithm
    clk_total = clock();
    
    for (int n=0; n<NUM_SWEEPS; n++) {
        // select submatrix indices
        for (int i=0; i<(M-1); i++) {
            for (int j=i+1; j<M; j++) {
                int theta_s, theta_d, ltheta, rtheta, sum, sumb, diff, diffb, lcos, lsin, rcos, rsin;
                int32_t v_temp;
                int16_t r_U[M][M], r_Vt[M][M], r_Ut[M][M], r_V[M][M];     
                
                // calculate rotation angles
                
                // start timer for rotation angle calculations
                clk = clock();
                int16_t mat_M_j_i = mat_M[j][i];
                int16_t mat_M_j_j = mat_M[j][j];
                int16_t mat_M_i_j = mat_M[i][j];
                int16_t mat_M_i_i = mat_M[i][i];

                //sum = mat_M[j][i] + mat_M[i][j];
                //diffb = mat_M[j][j] + mat_M[i][i];
                __asm__ __volatile__ (
                    " qadd16 %0 , %1 , %2\n\t"
                    : "=r" ( v_temp )
                    : "r" (mat_M_j_i + (mat_M_j_j<<16)), "r" (mat_M_i_j + (mat_M_i_i<<16))
                );
                sum = (int16_t)(v_temp & 0x0000FFFF);
                diffb = (v_temp >> 16);
                
                //sumb = mat_M[j][j] - mat_M[i][i];
                //diff = mat_M[j][i] - mat_M[i][j];
                __asm__ __volatile__ (
                    " qsub16 %0 , %1 , %2\n\t"
                    : "=r" ( v_temp )
                    : "r" (mat_M_j_j + (mat_M_j_i<<16)), "r" (mat_M_i_i + (mat_M_i_j<<16))
                );
                sumb = (int16_t)(v_temp & 0x000FFFF); 
                diff = (v_temp >> 16);
                
                printf("----------------\n");
                printf("sum: %d, sumb: %d\n", sum, sumb);
                theta_s = arctan2(sum, sumb);
                arctan2_ver1(sum, sumb);

                printf("\n");

                print("diff: %d, diffb: %d\n", diff, diffb);
                theta_d = arctan2(diff, diffb);
                arctan2_ver1(diff, diffb);
                printf("----------------\n");

                ltheta = (theta_s - theta_d + 1) >> 1;  
                rtheta = (theta_s + theta_d + 1) >> 1;

                cordic(&lcos, &lsin, ltheta);                
                cordic(&rcos, &rsin, rtheta);
                
                // stop angles timer
                clk_angles += clock() - clk;
                
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
                
                // apply rotations to M and update U and V
                //T2dot_productM(U, r_U, U);
                transposeM(r_U, r_Ut);
                dot_productM(r_U, mat_M, mat_M);
                dot_productM(U, r_Ut, U);
                
                transposeM(r_Vt, r_V);
                dot_productM(mat_M, r_Vt, mat_M);
                dot_productM(r_V, Vt, Vt);
                //T1dot_productM(r_Vt, Vt, Vt);
                
                // stop rotations timer
                clk_rota += clock() - clk;
                
                //print_matrixM(mat_M);
            }
        }
        //print_matrixM(mat_M);
    }
    
    
    clk_total = clock() - clk_total;
    printf("%d sweeps, took %.0f microseconds total\ncalculating angles took %.0fus (%.0f avg), rotating M and updating MUV took %.0fus (%.0f avg)\n\n", NUM_SWEEPS, 1000000*(double)clk_total/(CLOCKS_PER_SEC), 1000000*(double)clk_angles/(CLOCKS_PER_SEC), 1000000*(double)clk_angles/(CLOCKS_PER_SEC*16*NUM_SWEEPS), 1000000*(double)clk_rota/(CLOCKS_PER_SEC), 1000000*(double)clk_rota/(CLOCKS_PER_SEC*16*NUM_SWEEPS));
    print_matrixM(mat_M);
    
    return EXIT_SUCCESS;
}
