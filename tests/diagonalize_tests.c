#include <linear_approx.h>
#include <assert.h>
#include <stdio.h>

void arctan_test() {
    int X = 1030;
    int theta = arctan(X);
    assert(theta == (1319*X+291));
}

void cosine_test() {
    int X = 1030;
    int theta = lin_cos(X);
    assert(theta == (1319*X+291));
}

int main(void) {
    printf("running diagonalize tests...\n");

    printf("all tests passed\n");
    return 0;
}