#include "arctan.h"
#include <math.h>
#include <stdio.h>
int main(int argc, char * argv[]) {
    int x;
    double UPPER_BOUND = (double)pow(2, N_BITS - 1);

    double error;
    double min;
    double max;
    for (x = -3000; x < 3000; ++x) {
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
    return 0;
}