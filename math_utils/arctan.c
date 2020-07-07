
#include "linear_approx.h"
#include <stdio.h>
#include <math.h>
#include "arctan_hash_lookup_array.h"
#include <stdlib.h>
#define FLOAT_INCREMENT 0.01

int lin_arctan(int x) {
    //printf("input x = %d\n", x);
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
        result = -1*((OUTER_BOUNDS_SLOPE * x) - OUTER_BOUNDS_INTERCEPT);
    }
    return result;
}

int X_hash(int X) {
    //return ((X + 8192.0) / 410.0) + 0.2;
    return (X >> 5) + 512;
}

void generate_arctan_table_output() {
    double MIN_ANGLE = -1.0; // * (1 << (N_BITS - 1));
    double MAX_ANGLE = 1.0; //(1 << (N_BITS - 1));
    int X = 0;
    int int_output = 0;
    int i = 0;
    int size = 1200;
    int arr[1200];
    for (int j = 0; j < size; ++j) {
        arr[j] = 0;
    }
    for (double x = MIN_ANGLE; x < MAX_ANGLE; x += FLOAT_INCREMENT) {
        X = x * (1 << (N_BITS - 1));
        int_output = atan(x) * (1 << (N_BITS - 1));
        printf("hash = %d, X = %d, artcan(X) = %d\n", X_hash(X), X, int_output);
        //printf("X_hash = i = %f, result = %d\n", X_hash(X), int_output);
        int _i = X_hash(X);
        arr[_i] = int_output;
        i++;
    }
    for (int j = 0; j < size; ++j) {
        //printf("%d,\n", arr[j]);
    }
}

int getUpperValue(index) {
    int result = 0;
    for (int i = 0; i < 400; ++i) {
        result = arctan_lookup[index + i];
        //printf("  upper value search: %d\n", result);
        if (result != 0) {
            printf("upper index = %d\n", index + i);
            return result;
        }
    }
    printf("        ERROR: COULDN'T FIND UPPER VALUE\n");
    return result;
}

int getLowerValue(index) {
    int result = 0;
    for (int i = 0; i < 400; ++i) {
        result = arctan_lookup[index - i];
        //printf("  lower index search: %d\n", index - i);
        if (result != 0) {
            printf("lower index = %d\n", index - i);
            return result;
        }
    }
    printf("        ERROR: COULDN'T FIND LOWER VALUE\n");
    return result;
}

int table_interpolation(int X) {
    if (X == 0) {
        return 0;
    }
    int index = X_hash(X);
    int result = 0;
    if (ARCTAN_LOOKUP_MIN_INDEX <= index && index <= ARCTAN_LOOKUP_MAX_INDEX) {
        //printf("index = %d\n", index);
        result = arctan_lookup[index];
        //if (result != 0) {
        //    printf("index = %d\n", index);
        //    return result;
        //}
        //printf("input index: %d\n", index);
        //int upper_value = getUpperValue(index);
        //int lower_value = getLowerValue(index);
        //printf("upper value = %d\n", upper_value);
        //printf("lower value = %d\n", lower_value);
        //result =  (upper_value + lower_value) >> 1;
        //printf("    result = %d\n", result);
        return result;
    }
    //printf("        OUT OF BOUNDS INPUT X: %d, lookup index = %d\n", X, index);
    return result;
}

int decide_method(int X) {
    int result = 0;
    printf("X = %d\n", X);
    if (X < 2375) {
        // use table
        return 1;
    } else {
        // use linear approximation
        return 0;
    }
    return result;
}

int arctan(int X) {
    //if (decide_method(X)) {
    //    return table_interpolation(X);
    //} else {
    //    return lin_arctan(X) >> (N_BITS - 1);
    //}
    return table_interpolation(X);
}

double arctan_double(double x) {
    int UPPER_BOUND = 1 << (N_BITS - 1);

    int X = x * UPPER_BOUND;
    double result = ((double)arctan(X) / ((double)UPPER_BOUND));
    //if (decide_method(X) == 0) {
    //    result /= UPPER_BOUND;
    //}
    return result;
}