#include <diagonalize.h>
#include <linear_approx.h>
#include <linear_approx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main(void) {
    //double result = arctan((49.974+72.829)/(33.248-44.157));
    //result = arctan(151);
    //printf("%f\n", result);
    //result = arctan((49.974-72.829)/(33.248+44.157));
    //printf("%f\n", result);
    int max_val = pow(2, N_BITS);


    int input[M][M] = {
        {31, 77, -11, 26},
        {-42, 14, 79, -53},
        {-68, -10, 45, 90},
        {34, 16, 38, -19}
    };
    
    //int input[M][M] = {
    //    {31, 77, -11, 26, 88, 66},
    //    {-42, 14, 79, -53, 76, 34},
    //    {-68, -10, 45, 90, 23, 48},
    //    {34, 16, 38, -19, 11, 21},
    //    {14, 44, 34, 10, 22, 19},
    //    {34, 44, 33, 12, 21, 98}
    //};

    double** matrix = (double**)malloc(sizeof(double**) * M);
    for (int i = 0; i < M; ++i) {
        matrix[i] = (double*)malloc(sizeof(double*) * M);
    }
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            matrix[i][j] = input[i][j];
        }
    }

    printout("input matrix", matrix);
    printf("\n");
    SVD svd = diagonalize(matrix);

    return 0;
}