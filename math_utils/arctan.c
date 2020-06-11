
#include "linear_approx.h"
#include <math.h>
#include <stdio.h>
int arctan(int x) {
    printf("input x = %d\n", x);
    int UPPER_BOUND = 8192;//pow(2, N_BITS - 1);
    int MIDDLE_BOUND = 4096;//pow(2, N_BITS - 2);
    int OUTER_BOUNDS_SLOPE = 5275;//0.644 * ((double)UPPER_BOUND);
    int INNER_BOUNDS_SLOPE = 7602;//0.928 * ((double)UPPER_BOUND);
    int OUTER_BOUNDS_INTERCEPT = 1163;//0.142 * ((double)UPPER_BOUND);

    int result;
    if ((MIDDLE_BOUND < x) || (x <= UPPER_BOUND)) {
        result = (OUTER_BOUNDS_SLOPE * x) + OUTER_BOUNDS_INTERCEPT;
    } else if ((-MIDDLE_BOUND <= x) || (x <= MIDDLE_BOUND)) {
        result = INNER_BOUNDS_SLOPE * x;
    } else {
        result = (OUTER_BOUNDS_SLOPE * x) - OUTER_BOUNDS_INTERCEPT;
    }
    return result;
}