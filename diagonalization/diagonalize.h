#ifndef M
#define M 4

typedef struct svd_struct {
    int*** U;
    int*** S;
    int*** V;
} SVD;

void initIdentityMatrix(int** matrix);
int dotProduct(int* v1, int* v2);
void transpose(int** source, int** dest);
void matmul(int** m1, int** m2, int** dest);
void applyRotations(SVD svd, int i, int j, double theta_l, double theta_r);
void applyJacobiMethod(SVD svd, int i, int j);
void sweep(int row, int col, SVD svd);
void startSweeps(SVD svd);
SVD diagonalize(int** matrix);
void printout(const char * matrixName, int** matrix);
void printoutSVD(SVD svd);
#endif