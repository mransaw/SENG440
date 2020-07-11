#include "linear_approx.h"
#include <stdio.h>
#include <math.h>

void generate_linear_approximation(double min, double max, double inc) {
    double SCALE_IN = pow(2, SF_ATAN_IN);
    double SCALE_OUT = pow(2, SF_ATAN_OUT);
    double SLOPE_SF = SCALE_OUT / SCALE_IN;
    int intervals = (max - min) / inc;
    double slopes[intervals];
    double intercepts[intervals];
    double lower_x = min;
    double upper_x = min + inc;
    int i = 0;
    while (upper_x <= max) {
        slopes[i] = SLOPE_SF * ((atan(upper_x) - atan(lower_x)) / (upper_x - lower_x));
        double avg_x = (lower_x + upper_x) / 2.0;
        double slope_result = (slopes[i] * (SCALE_IN));
        double atan_result = atan(avg_x) * SCALE_OUT;
        double percent_diff = 100 * fabs(slope_result - atan_result) / atan_result;
        //printf("    slope result = %f, atan result = %f\n, diff = %f, percent diff = %f\n", slope_result, atan_result, slope_result - atan_result, percent_diff);
        intercepts[i] = atan_result - slope_result;
        int lower_X = lower_x * SCALE_IN;
        int upper_X = upper_x * SCALE_IN;
        if (lower_x == min) {
            printf("if (%d <= X && X < %d) { slope *= %d; \n intercept *= %d; }\n", lower_X, upper_X , (int)slopes[i], (int)intercepts[i]);
        }
        else {
            printf("else if (%d <= X && X < %d) { slope *= %d; \n intercept *= %d; }\n", lower_X , upper_X , (int)slopes[i], (int)intercepts[i]);
        }
        upper_x += inc;
        lower_x += inc;
        ++i;
    }
}

void eval_error() {
    double max_error = 0;
    double error = 0;
    double inc = 0.001;
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
    return int_arctan(X) >> 1;
}

int arccot(int X) {
    return 0;
}

int adjust_angle(int arccot, int X) {
    return 0;
}

int int_arctan(int X) {
    double scale_in = pow(2, SF_ATAN_IN);
    double scale_out = pow(2, SF_ATAN_OUT) / M_PI;
    double slope = 1;
    double intercept = 1;
    return (slope * X + intercept);
}