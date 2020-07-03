#include <linear_approx.h>
#include <stdio.h>
#include <math.h>

int UPPER_BOUND = 1 << (N_BITS - 1);

void arctan_tests() {
    int size = 20;
    float theta = -1.0;
    for (int i = 0; i < size; ++i) {
        theta += 0.1;
        float r1 = atan(theta);
        int int_theta = theta * UPPER_BOUND;
        printf("theta: %f, int_theta: %d\n", theta, int_theta);
        int r2 = arctan(int_theta);
        float float_r2 = (double)r2 / ((double)(UPPER_BOUND * UPPER_BOUND));
        printf("%f\n", r1);
        printf("%f\n", float_r2);
    }
}

void lin_cos_tests() {

}

void lin_sin_tests() {

}

int main(void) {
    arctan_tests();
    //printf("---------\n");
    //lin_cos_tests();
    //printf("---------\n");
    //lin_sin_tests();
    //printf("---------\n");
    return 0;
}