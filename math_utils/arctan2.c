#include <linear_approx.h>
#include <stdio.h>
#include <math.h>
#define HALF_UNIT_CIRCLE_DEGREES 180

int angles[] = {
    12867,
    6433,
    3216,
    1608,
    804,
    402,
    201,
    100,
    50,
    25,
    12,
    6,
    3,
    1,
    0
};

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

int int_angles[] = {
    435241,
    229969,
    116736,
    58594,
    29325,
    14666,
    7333,
    3666,
    1833,
    916,
    458,
    229,
    114,
    57,
    28
};

void generate_angles_table() {
    double max_angle = M_PI / 4;
    int k = 0;
    for (double i = 1; k < 16; i /= 2) {
        ++k;
        double angle = d_angles[k] * pow(2, SF_ATAN_OUT);
        if (i == 0) {
            printf("    %f\n", angle);
            break;
        }
        printf("    %f,\n", angle);
    }
}

void d_generate_angles_table() {
    double max_angle = M_PI / 4;
    int k = 0;
    for (double i = 1; k < 16; i /= 2) {
        ++k;
        double angle = atan(i) * 180 / M_PI;
        if (i == 0) {
            printf("    %f\n", angle);
            break;
        }
        printf("    %f,\n", angle);
    }
}

double d_arctan2(double y, double x) {
    printf("x= %f, y = %f\n", x, y);
    double z = 0;
    double sigma = 1.0;
    printf("z = %f\n", z);
    double x_ = x;
    double y_ = y;
    for (int i = 0; i < 16; ++i) {
        if (y_ >= 0) {
            sigma = -1.0;
        } else {
            sigma = 1.0;
        }
        double delta_x = - (sigma * (pow(2, -i)) * y_);
        double delta_y = + (sigma * (pow(2, -i)) * x_);;
        x_ = x_ + delta_x;
        y_ = y_ + delta_y;
        z = z - (sigma * d_angles[i]);
        //printf("\nx = %f\n y = %f\n z = %f\n\n", x_, y_, z);
    }
    printf("result: %f, expected: %f\n", z, atan2(y, x) * 180 / M_PI);
    return z;
}

int phase_shift(int Y, int X, int z) {
    int adjusted_z = z;
    if (X <= 0 && Y <= 0) { // quadrant 3
        adjusted_z = z + HALF_UNIT_CIRCLE_DEGREES;
    }
    return adjusted_z;
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
    if (Y - X <= 0) {
        return lin_arctan(Y, X);
    } else {
        return cordic_arctan(Y, X);
    }
}