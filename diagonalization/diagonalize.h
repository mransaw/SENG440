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

#define ITER 14
#define KN 79595
#define NUM_SWEEPS 10
#define M 6

extern const int angles[14];

void cordic(int16_t* cos, int16_t* sin, int angle);
void dot_productM(int16_t m1[restrict M][M], int16_t m2[restrict M][M], int16_t dest[M][M]);
void transposeM(int16_t source[restrict M][M], int16_t dest[M][M]);
void print_matrix2(int16_t matrix[2][2]);
void print_matrixM(int16_t matrix[M][M]);
void print_descaled(int16_t matrix[M][M]);
