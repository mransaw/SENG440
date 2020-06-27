#ifndef M
#define M 6
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