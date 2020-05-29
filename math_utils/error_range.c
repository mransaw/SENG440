#include "arctan.h"
#include <math.h>
#include <stdio.h>
int main(int argc, char * argv[]) {
    int x;
    double error;
    double min;
    double max;
    for (x = -3000; x < 3000; ++x) {
        printf("arctan(%f) = %f\n", (double)x/2048.0, ((double)arctan(x))/(2048.0 * 2048.0));
        printf("    atan(%f) = %f\n", (double)x/2048.0, atan(x/2048.0));
        error = fabs((arctan(x) / (2048.0 * 2048.0)) - atan(x / 2048.0));
        if (error < min) {
            min = error;
        } else if (error > max) {
            max = error;
        }
    }
    printf("error range: %f to %f\n", min, max);
    return 0;
}