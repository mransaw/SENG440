#ifndef M

typedef struct svd_struct {
    double*** U;
    double*** S;
    double*** V;
} SVD;

void initIdentityMatrix(double** matrix);
double dotProduct(double* v1, double* v2);
void transpose(double** source, double** dest);
void matmul(double** m1, double** m2, double** dest);
void applyRotations(SVD svd, int i, int j, double theta_l, double theta_r);
void applyJacobiMethod(SVD svd, int i, int j);
void sweep(SVD svd);
SVD diagonalize(double** matrix);
void printout(const char * matrixName, double** matrix);
void printoutSVD(SVD svd);
#endif

#include <stdint.h>
#include <string.h>

#define ITER 12
#define KN 79595
#define NUM_SWEEPS 10
#define N_TIMES 10
#define M 6

extern const int angles[14];

void cordic(int* cos, int* sin, int angle);
void dot_productM(int m1[M][M], int m2[M][M], int dest[M][M]);
void transposeM(int source[M][M], int dest[M][M]);
void print_matrix2(int matrix[2][2]);
void print_matrixM(int matrix[M][M]);
void print_descaled(int matrix[M][M]);
