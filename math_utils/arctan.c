
#include "linear_approx.h"
#include <math.h>

int arctan(int x) {
    int UPPER_BOUND = pow(2, N_BITS - 1);
    int MIDDLE_BOUND = pow(2, N_BITS - 2);
    int OUTER_BOUNDS_SLOPE = ceil(0.644 * ((double)UPPER_BOUND));
    int INNER_BOUNDS_SLOPE = ceil(0.928 * ((double)UPPER_BOUND));
    int OUTER_BOUNDS_INTERCEPT = ceil(0.142 * ((double)UPPER_BOUND));

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