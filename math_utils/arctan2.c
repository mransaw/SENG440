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

int divide_by_multiply(int Y, int X) {
    if (X == 0) {
        return 0;
    }
    //int lower = -1 * (1 << ((SF_ATAN_IN * 2 )- 1));
    //int upper = (1 << ((SF_ATAN_IN * 2) - 1)) - 1;
    //int result = (lower + upper) >> 1;
    //int challenger = 1;
    //int delta = 0;
    //while (1) {
    //    printf("challenger = %d\n", challenger);
    //    printf("result = %d\n", result);
    //    printf("X = %d\n", X);
    //    printf("result * X = %f, Y = %d\n", result * X, Y);
    //    challenger = (result * X) - Y;
    //    if (challenger > delta) {
    //        upper = result;
    //        result = (lower + upper) >> 1;
    //    } else if (challenger < delta) {
    //        lower = result;
    //        result = (lower + upper) >> 1;
    //    } else {
    //        break;
    //    }
    //}
    //return result >> SF_ATAN_IN; // adjustment for squared scale factor upon muliplication
    return (Y << SF_ATAN_IN)/X;
}

int lin_arctan(int Y, int X) {
    int div_YX = divide_by_multiply(Y, X);
    int scale_in = 1 << SF_ATAN_IN;
    int scale_out = divide_by_multiply((1 << SF_ATAN_IN),  M_PI * pow(2, SF_ATAN_IN));
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
    int z = 0;
    if (Y == -8192 || X == -8192) {
        z = 90;
    }else if (Y - X <= 0) {
        z = lin_arctan(Y, X);
    } else {
        z = cordic_arctan(Y, X);
    }
    z = divide_by_multiply(z, 180 << SF_ATAN_IN);
    return z;
}