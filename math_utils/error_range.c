#include "linear_approx.h"
#include <math.h>
#include <stdio.h>

void arctan_error() {
    int x;
    double UPPER_BOUND = (double)pow(2, N_BITS - 1);

    double error;
    double min;
    double max;
    for (x = -UPPER_BOUND; x < UPPER_BOUND; ++x) {
        printf("arctan(%f) = %f\n", UPPER_BOUND, ((double)arctan(x))/(UPPER_BOUND * UPPER_BOUND));
        printf("    atan(%f) = %f\n", UPPER_BOUND, atan(x/UPPER_BOUND));
        error = fabs((arctan(x) / (UPPER_BOUND * UPPER_BOUND)) - atan(x / UPPER_BOUND));
        if (error < min) {
            min = error;
        } else if (error > max) {
            max = error;
        }
    }
    printf("error range: %f to %f\n", min, max);
}

void sin_error() {
    int x;
    double UPPER_BOUND = (double)pow(2, N_BITS - 1);
    double error;
    double min;
    double max;
    for (x = -3000; x < 3000; ++x) {
        printf("lin_sin(%f) = %f\n", UPPER_BOUND, ((double)lin_sin(x))/(UPPER_BOUND * UPPER_BOUND));
        printf("    sin(%f) = %f\n", UPPER_BOUND, sin(x/UPPER_BOUND));
        error = fabs((lin_sin(x) / (UPPER_BOUND * UPPER_BOUND)) - sin(x / UPPER_BOUND));
        if (error < min) {
            min = error;
        } else if (error > max) {
            max = error;
        }
    }
    printf("error range: %f to %f\n", min, max);
}

void cos_error() {
    int x;
    double UPPER_BOUND = (double)pow(2, N_BITS - 1);
    double error;
    double min;
    double max;
    for (x = -3000; x < 3000; ++x) {
        printf("lin_cos(%f) = %f\n", UPPER_BOUND, ((double)lin_cos(x))/(UPPER_BOUND * UPPER_BOUND));
        printf("    cos(%f) = %d\n", UPPER_BOUND, lin_cos(x/UPPER_BOUND));
        error = fabs((lin_cos(x) / (UPPER_BOUND * UPPER_BOUND)) - cos(x / UPPER_BOUND));
        if (error < min) {
            min = error;
        } else if (error > max) {
            max = error;
        }
    }
    printf("error range: %f to %f\n", min, max);
}

int main(void) {
    arctan_error();
    return 0;
}