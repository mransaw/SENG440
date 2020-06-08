#ifndef M
#define M 6

typedef struct svd_struct {
    int** U;
    int** S;
    int** V;
} SVD;

void initIdentityMatrix(int** matrix);
int dotProduct(int* v1, int* v2);
void transpose(int** source, int** dest);
void matmul(int** m1, int** m2, int** dest);
void applyRotations(SVD svd, int i, int j, int theta_l, int theta_r);
void applyJacobiMethod(SVD svd, int i, int j);
void sweep(int row, int col, SVD svd);
void startSweeps(SVD svd);
SVD diagonalize(int** matrix);
void printout(const char * matrixName, int** matrix);

#endif