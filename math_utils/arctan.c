#include "linear_approx.h"
#include <stdio.h>
#include <math.h>

double interceptAverageWithinRange(double slope, double lower_x, double upper_x, double step) {
    double x = lower_x;
    double accumulate = 0;
    double n = 1;
    while (x < upper_x) {
        double atan_diff = (atan(x) * pow(2, SF_ATAN_OUT-1)/M_PI) - (slope * x * pow(2, SF_ATAN_IN));
        accumulate += atan_diff;
        x += step;
        ++n;
    }
    return (accumulate / n);
}

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
        slopes[i] = SLOPE_SF * pow(2, SF_ATAN_OUT) * ((atan(upper_x) - atan(lower_x)) / (upper_x - lower_x));
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

    if (-16384 <= X && X < -14745) { 
    slope *= 1371; 
    intercept *= -11107592; 
    }
    else if (-14745 <= X && X < -13107) { 
    slope *= 1514; 
    intercept *= -8998046; 
    }
    else if (-13107 <= X && X < -11468) { 
    slope *= 1669; 
    intercept *= -6969148; 
    }
    else if (-11468 <= X && X < -9830) { 
    slope *= 1833; 
    intercept *= -5088702; 
    }
    else if (-9830 <= X && X < -8192) { 
    slope *= 2001; 
    intercept *= -3431659; 
    }
    else if (-8192 <= X && X < -6553) { 
    slope *= 2167; 
    intercept *= -2070212; 
    }
    else if (-6553 <= X && X < -4915) { 
    slope *= 2322; 
    intercept *= -1058192; 
    }
    else if (-4915 <= X && X < -3276) { 
    slope *= 2452; 
    intercept *= -411880; 
    }
    else if (-3276 <= X && X < -1638) { 
    slope *= 2548; 
    intercept *= -93139; 
    }
    else if (-1638 <= X && X < 0) { 
    slope *= 2598; 
    intercept *= -3531; 
    }
    else if (0 <= X && X < 1638) { 
    slope *= 2598; 
    intercept *= 3531; 
    }
    else if (1638 <= X && X < 3276) { 
    slope *= 2548; 
    intercept *= 93139; 
    }
    else if (3276 <= X && X < 4915) { 
    slope *= 2452; 
    intercept *= 411880; 
    }
    else if (4915 <= X && X < 6553) { 
    slope *= 2322; 
    intercept *= 1058192; 
    }
    else if (6553 <= X && X < 8191) { 
    slope *= 2167; 
    intercept *= 2070212; 
    }
    else if (8191 <= X && X < 9830) { 
    slope *= 2001; 
    intercept *= 3431659; 
    }
    else if (9830 <= X && X < 11468) { 
    slope *= 1833; 
    intercept *= 5088702; 
    }
    else if (11468 <= X && X < 13107) { 
    slope *= 1669; 
    intercept *= 6969148; 
    }
    else if (13107 <= X && X < 14745) { 
    slope *= 1514; 
    intercept *= 8998046; 
    }
    else if (14745 <= X && X < 16383) { 
    slope *= 1371; 
    intercept *= 11107592; 
    }
    return (slope * X + intercept);
}