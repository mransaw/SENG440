
#include "linear_approx.h"
#include <stdio.h>
#include <math.h>

#define INCREMENT 500

int arctan_lookup_array[] = {
    -6433,
    -6176,
    -5902,
    -5611,
    -5302,
    -4974,
    -4627,
    -4261,
    -3874,
    -3468,
    -3043,
    -2600,
    -2141,
    -1668,
    -1183,
    -690,
    -191,
    307,
    805,
    1297,
    1779,
    2249,
    2705,
    3143,
    3564,
    3966,
    4347,
    4709,
    5052,
    5375,
    5680,
    5967,
    6237
};

int linear_approximation(int x) {
    printf("input x = %d\n", x);
    int UPPER_BOUND = 1 << (N_BITS - 1);
    int MIDDLE_BOUND = 1 << (N_BITS - 2);
    int OUTER_BOUNDS_SLOPE = 5275; //0.644 * UPPER_BOUND
    int INNER_BOUNDS_SLOPE = 7602; //0.928 * UPPER_BOUND
    int OUTER_BOUNDS_INTERCEPT = 9527296; //0.142 * UPPER_BOUND * UPPER_BOUND

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

int arctan_table() {
    int result;
    int MIN = -1 * (1 << (N_BITS - 1));
    int MAX = (1 << (N_BITS - 1));
    for (int i = MIN; i < MAX; i+=INCREMENT) {
        printf("%d %f\n", i, (1 << (N_BITS - 1)) * atan(((double)i) / ((double)(MAX))));
    }
    return result;
}

int table_interpolation(int x) {
    int upper_value = arctan_lookup_array[(x + INCREMENT) % INCREMENT];
    int lower_value = arctan_lookup_array[x % INCREMENT];
    return (upper_value + lower_value) / 2;
}

int arctan(int x) {
    return table_interpolation(x);
}