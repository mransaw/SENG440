#include <linear_approx.h>
#include <stdio.h>
#include <math.h>

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
    45.00,
    26.56,
    14.04,
    7.13,
    3.58,
    1.79,
    0.89,
    0.45
};

void generate_angles_table() {
    int max_angle = (1 << SF_ATAN_IN) * M_PI / 4;
    for (int i = max_angle; i >= 0; i /= 2) {
        if (i == 0) {
            printf("    %d\n", i);
            break;
        }
        printf("    %d,\n", i);
    }
}

void d_generate_angles_table() {
    double max_angle = M_PI / 4;
    int k = 0;
    for (double i = 1; k < 16; i /= 2) {
        ++k;
        if (i == 0) {
            printf("    %f\n", atan(pow(2, i)));
            break;
        }
        printf("    %f,\n", atan(pow(2, i)));
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
        //printf("x = %f\n", delta_x);
        //printf("y = %f\n", delta_y);
        //printf("z = %f\n", -(sigma * d_angles[i]));
        z = z - (sigma * d_angles[i]);
        printf("\nx = %f\n y = %f\n z = %f\n\n", x_, y_, z);
    }
    printf("result: %f, expected: %f\n", z, atan2(y, x)*180/M_PI);
    return z;
}

int arctan2(int Y, int X) {
    return 0;
    int result = 0;
    int X_ = 0;
    int Y_ = 0;
    int sum = 0;
    for (int i = 0; i < 16; ++i) {
        printf("sum = %d\n", sum);
        if (Y > 0) {
            X_ = X + (Y >> i);
            Y_ = Y - (X >> i);
            printf("X_ = %d\n", X_);
            printf("Y_ = %d\n", Y_);
            sum += angles[i];
        } else if (Y < 0) {
            X_ = X - (Y >> i);
            Y_ = Y + (X >> i);
            printf("X_ = %d\n", X_);
            printf("Y_ = %d\n", Y_);
            sum -= angles[i];
        }
    }
    printf("result = %f\n", (double)sum / (1 << SF_ATAN_IN) / M_PI);
    return sum;
}

//int d_arctan2(int Y, int X) {
//    int result = 0;
//    int X_ = 0;
//    int Y_ = 0;
//    int sum = 0;
//    for (int i = 0; i < 16; ++i) {
//        printf("sum = %d\n", sum);
//        if (Y > 0) {
//            X_ = X + (Y >> i);
//            Y_ = Y - (X >> i);
//            sum += angles[i];
//        } else if (Y < 0) {
//            X_ = X - (Y >> i);
//            Y_ = Y + (X >> i);
//            sum -= angles[i];
//        }
//    }
//    printf("result = %f\n", (double)sum);
//    return sum;
//}
