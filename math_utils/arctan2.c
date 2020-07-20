#include <linear_approx.h>
#include <stdio.h>
#include <math.h>
#define HALF_UNIT_CIRCLE_DEGREES 180
#define SCALED_PI 51471 // 3.14 * pow(2, 14)
#define SCALE_IN (1 << SF_ATAN_IN)

double d_angles[] = {
    45.000000,
    26.565051,
    14.036243,
    7.125016,
    3.576334,
    1.789911,
    0.895174,
    0.447614,
    0.223811,
    0.111906,
    0.055953,
    0.027976,
    0.013988,
    0.006994,
    0.003497,
    0.001749
};

int int_angles[] = { // radians * pow(2, SF_ATAN_OUT)
    25736,
    15193,
    8027,
    4075,
    2045,
    1024,
    512,
    256,
    128,
    64,
    32,
    16,
    8,
    4,
    2,
    1
};

int phase_shift(int Y, int X, int z) {
    int adjusted_z = z;
    if (X <= 0 && Y <= 0) { // quadrant 3
        adjusted_z = z + HALF_UNIT_CIRCLE_DEGREES;
    }
    return adjusted_z;
}

// division method assuming N and D are of similar magnitude 
int divide_by_subraction(int N, int D) { /// inputs are Q16.14 (31 bit signed integers)
    N = N << SF_ATAN_IN;
    int Q = 0;
    int R = 0;
    int n = N - D;
    if (N < 0 && D > 0) { // negative N and positive D, take negative of result with positive args
        int _N = -(N >> SF_ATAN_IN);
        return -divide_by_subraction(_N, D); // N must be scaled back, before being passed back into recursion
    } else if (D < 0) { // positive N and negative D, or both negative: take result with flipped sign args
        int _N = -(N >> SF_ATAN_IN); // N must be scaled back, before being passed back into recursion
        int _D = -D;
        return divide_by_subraction(_N, _D);
    }
    while (n > 0) {
        n -= D;
        if (n > 0) {
            ++Q; // only increment Q if the next loop is guaranteed to run, when n > 0
        } else {
            R = n;
            break;
        }
    }
    return Q; // returns quotient of N / D, scaled by 2^SF_ATAN_IN
}

int lin_arctan(int Y, int X) {
    int div_YX = divide_by_subraction(Y, X);
    int slope = 1;
    int intercept = 1;

    if (-16384 <= div_YX && div_YX < -14745) { 
    slope *= 1371; 
    intercept *= -11107592; 
    }
    else if (-14745 <= div_YX && div_YX < -13107) { 
    slope *= 1514; 
    intercept *= -8998046; 
    }
    else if (-13107 <= div_YX && div_YX < -11468) { 
    slope *= 1669; 
    intercept *= -6969148; 
    }
    else if (-11468 <= div_YX && div_YX < -9830) { 
    slope *= 1833; 
    intercept *= -5088702; 
    }
    else if (-9830 <= div_YX && div_YX < -8192) { 
    slope *= 2001; 
    intercept *= -3431659; 
    }
    else if (-8192 <= div_YX && div_YX < -6553) { 
    slope *= 2167; 
    intercept *= -2070212; 
    }
    else if (-6553 <= div_YX && div_YX < -4915) { 
    slope *= 2322; 
    intercept *= -1058192; 
    }
    else if (-4915 <= div_YX && div_YX < -3276) { 
    slope *= 2452; 
    intercept *= -411880; 
    }
    else if (-3276 <= div_YX && div_YX < -1638) { 
    slope *= 2548; 
    intercept *= -93139; 
    }
    else if (-1638 <= div_YX && div_YX < 0) { 
    slope *= 2598; 
    intercept *= -3531; 
    }
    else if (div_YX == 0) {
        slope = 0;
        intercept = 0;
    }
    else if (0 < div_YX && div_YX < 1638) { 
    slope *= 2598; 
    intercept *= 3531; 
    }
    else if (1638 <= div_YX && div_YX < 3276) { 
    slope *= 2548; 
    intercept *= 93139; 
    }
    else if (3276 <= div_YX && div_YX < 4915) { 
    slope *= 2452; 
    intercept *= 411880; 
    }
    else if (4915 <= div_YX && div_YX < 6553) { 
    slope *= 2322; 
    intercept *= 1058192; 
    }
    else if (6553 <= div_YX && div_YX < 8191) { 
    slope *= 2167; 
    intercept *= 2070212; 
    }
    else if (8191 <= div_YX && div_YX < 9830) { 
    slope *= 2001; 
    intercept *= 3431659; 
    }
    else if (9830 <= div_YX && div_YX < 11468) { 
    slope *= 1833; 
    intercept *= 5088702; 
    }
    else if (11468 <= div_YX && div_YX < 13107) { 
    slope *= 1669; 
    intercept *= 6969148; 
    }
    else if (13107 <= div_YX && div_YX < 14745) { 
    slope *= 1514; 
    intercept *= 8998046; 
    }
    else if (14745 <= div_YX && div_YX < 16383) { 
    slope *= 1371; 
    intercept *= 11107592; 
    }
    return (slope * div_YX + intercept);
}

int cordic_arctan(int Y, int X) {
    int z = 0;
    int X_ = X;
    int Y_ = Y;
    int delta_x = 0;
    int delta_y = 0;
    for (int i = 0; i < 16; ++i) {
        if (Y_ >= 0) {
            delta_x = + (Y_ >> i);
            delta_y = - (X_ >> i);
            X_ = X_ + delta_x;
            Y_ = Y_ + delta_y;
            z = z + int_angles[i]; // Q16.15 - Q16.15 --> Q16.15 result
        } else {
            delta_x = - (Y_ >> i);
            delta_y = + (X_ >> i);
            X_ = X_ + delta_x;
            Y_ = Y_ + delta_y;
            z = z - int_angles[i]; // Q16.15 - Q16.15 --> Q16.15 result
        }
    }
    return phase_shift(Y, X, z);
}

int arctan2(int Y, int X) {
    printf("--------\nY = %d, X = %d\n", Y, X);
    int z = 0;
    if (-SCALE_IN < Y && Y < SCALE_IN) {
        return 0;
    } else if (X == -8192) {
        return -51471;
    }
    z = cordic_arctan(Y, X);

    return z;
}