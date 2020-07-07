#include <linear_approx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int UPPER_BOUND = 1 << (N_BITS - 1);

void arctan_tests() {
    double theta = -1.0;
    double max_error = 0;
    while (theta <= 1.0) {
        theta += 0.01;
        double r1 = atan(theta);
        int X = theta * UPPER_BOUND;
        //printf("---------------\n");
        //printf("theta: %f, X: %d\n", theta, X);
        int r2 = table_interpolation(X);
        int r3 = lin_arctan(X);
        double table_value = ((double)r2 / ((double)(UPPER_BOUND)));
        double linear_approx_value = ((double)r3 / ((double)(UPPER_BOUND * UPPER_BOUND)));
        double result = ((double)arctan(X) / ((double)UPPER_BOUND));
        //if (decide_method(X) == 0) {
        //    result /= UPPER_BOUND;
        //}
        printf("table value = %f\n", table_value);
        printf("linear approx arctan = %f\n", linear_approx_value);
        printf("atan() = %f\n", r1);
        printf("decided value: %f\n", result);
        printf("----------------\n");
        if (fabs(result - r1) > max_error) {
            max_error = fabs(result - r1);
        }
    }
    printf("\n\nMAX ERROR: %f\n\n\n", max_error);
}

void lin_cos_tests() {

}

void lin_sin_tests() {

}

int main(void) {
    //generate_arctan_table_output();
    arctan_tests();
    //printf("---------\n");
    //lin_cos_tests();
    //printf("---------\n");
    //lin_sin_tests();
    //printf("---------\n");
    return 0;
}