#include <diagonalize.h>
#include <linear_approx.h>
#include <linear_approx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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