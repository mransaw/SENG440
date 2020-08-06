
#include <diagonalize.h>
#include <linear_approx.h>
#include <stdio.h>
#include <math.h>

#define HALF_UNIT_CIRCLE_DEGREES 180
#define SCALED_PI 51471 // 3.14 * pow(2, 14)
#define SCALE_IN (1 << SF_ATAN_IN)

/*int int_angles[] = { // radians * pow(2, SF_ATAN_OUT) / pi
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
};*/

int phase_shift(int Y, int X, int z) {
    int adjusted_z = z;
    if (X <= 0 && Y <= 0) { // quadrant 3
        adjusted_z = z + HALF_UNIT_CIRCLE_DEGREES;
    }
    return adjusted_z;
}

int cordic_arctan(int Y, int X) {
    int z = 0;
    int X_ = (X << 14);
    int Y_ = (Y << 14);
    
    if (X_ < 0) {
        X_ *= -1;
        Y_ *= -1;
    }
    
    int delta_x = 0;
    int delta_y = 0;
    
    for (int i = 0; i < ITER; ++i) {
        if (Y_ >= 0) {
            delta_x = + (Y_ >> i);
            delta_y = - (X_ >> i);
            X_ = X_ + delta_x;
            Y_ = Y_ + delta_y;
            z = z + angles[i]; // Q16.15 - Q16.15 --> Q16.15 result
        } else {
            delta_x = - (Y_ >> i);
            delta_y = + (X_ >> i);
            X_ = X_ + delta_x;
            Y_ = Y_ + delta_y;
            z = z - angles[i]; // Q16.15 - Q16.15 --> Q16.15 result
        }
        printf("arctan2 original: %d\n", z);
    }
    return z;//phase_shift(Y, X, z);
}

int arctan2_ver1(int Y, int X) {
    int z = 0;
    /*if (-SCALE_IN < Y && Y < SCALE_IN) {
        return 0;
    }*/
    z = cordic_arctan(Y, X);
    return z;
}
