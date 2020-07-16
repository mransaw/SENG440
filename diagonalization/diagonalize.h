#ifndef M
#define M 4
#define NUM_SWEEPS 4

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

#define ITER 6
#define KN 79595

extern const int16_t angles[6];

void cordic(int16_t* cos, int16_t* sin, int16_t angle);
void dot_productM(int16_t m1[M][M], int16_t m2[M][M], int16_t dest[M][M]);
void transposeM(int16_t source[M][M], int16_t dest[M][M]);
void print_matrix2(int16_t matrix[2][2]);
void print_matrixM(int16_t matrix[M][M]);
void print_descaled(int16_t matrix[M][M]);