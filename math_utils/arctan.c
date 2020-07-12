#include "linear_approx.h"
#include <stdio.h>
#include <math.h>

double interceptAverageWithinRange(double slope, double lower_x, double upper_x, double step) {
    double x = lower_x;
    double accumulate = 0;
    double n = 1;
    while (x < upper_x) {
        double atan_diff = (atan(x) * pow(2, SF_ATAN_OUT)/M_PI) - (slope * x * pow(2, SF_ATAN_IN));
        accumulate += atan_diff;
        x += step;
        ++n;
    }
    return (accumulate / n);
}

void generate_linear_approximation(double min, double max, double inc) {
    double SCALE_IN = pow(2, SF_ATAN_IN);
    double SCALE_OUT = pow(2, SF_ATAN_OUT) / M_PI;
    double SLOPE_SF = SCALE_OUT / SCALE_IN;
    int intervals = (max - min) / inc;
    double slopes[intervals];
    double intercepts[intervals];
    double lower_x = min;
    double upper_x = min + inc;
    int i = 0;

    while (upper_x <= max) {
        slopes[i] = SLOPE_SF * ((atan(upper_x) - atan(lower_x)) / (upper_x - lower_x));
        //printf("    slope result = %f, atan result = %f\n, diff = %f, percent diff = %f\n", slope_result, atan_result, slope_result - atan_result, percent_diff);
        intercepts[i] = interceptAverageWithinRange(slopes[i], lower_x, upper_x, inc / 20000);
        int lower_X = lower_x * SCALE_IN;
        int upper_X = upper_x * SCALE_IN;
        if (lower_x == min) {
            printf("if (%d <= X && X < %d) { \n slope *= %d; \n intercept *= %d; \n}\n", lower_X, upper_X , (int)(slopes[i]), (int)(intercepts[i]));
        }
        else {
            printf("else if (%d <= X && X < %d) { \n slope *= %d; \n intercept *= %d; \n}\n", lower_X, upper_X, (int)(slopes[i]), (int)(intercepts[i]));
        }
        upper_x += inc;
        lower_x += inc;
        ++i;
    }
}

void eval_error() {
    double max_error = 0;
    double error = 0;
    double inc = 0.1;
    for (double x = -1.0; x < 1.0; x += inc) {
        error = (int_arctan(x) - atan(x));
        printf("x = %f, int_arctan(x) = %d, atan(x) = %f, diff error: %f\n", x, int_arctan(x), atan(x), error);
        if (error > max_error) {
            max_error = error;
        }
    }
    for (double x = -8192; x <= 8192; x++) {
        error = (int_arctan(x)  - atan(x));
        printf("x = %f, int_arctan(x) = %d, atan(x) = %f, diff error: %f\n", x, int_arctan(x), atan(x), error);
        if (error > max_error) {
            max_error = error;
        }
    }
    printf("Max error: %f\n", max_error);
}

int arctan(int X) {
    return int_arctan(X);
}

int arccot(int X) {
    return 0;
}

int adjust_angle(int arccot, int X) {
    return 0;
}

int int_arctan(int X) {
    if (X == 0) {
        return 0;
    }
    double scale_in = pow(2, SF_ATAN_IN);
    double scale_out = pow(2, SF_ATAN_OUT) / M_PI;
    double slope = 1;
    double intercept = 1;

    if (-16384 <= X && X < -8192) { 
    slope *= 1677; 
    intercept *= -6601169; 
    }
    else if (-8192 <= X && X < -736) { 
    slope *= 2418; 
    intercept *= -370807; 
    }
    else if (736 < X && X < 8192) { 
    slope *= 2418; 
    intercept *= 370807; 
    }
    else if (8192 <= X && X < 16384) { 
    slope *= 1677; 
    intercept *= 6601169; 
    }
    return (slope * X + intercept);
}