
#include <diagonalize.h>
#include <linear_approx.h>
#include <stdio.h>
#include <math.h>

#define sign(val) (val >= 0) - (val < 0);

int cordic_arctan(int Y, int X) {
    int z = 0;
    int X_ = (X << 14);

    int Y_ = (Y << 14);
    X_ *= sign(X_);

    Y_ *= sign(Y_);
    int delta_x = 0;

    int s = sign(Y_);
    int delta_y = 0;

    int signed_angles = 1;
    for (int i = 0; i < ITER; ++i) {
        delta_x = s * (Y_ >> i);
        delta_y = -s * (X_ >> i);

        X_ = X_ + delta_x;
        Y_ = Y_ + delta_y;

        signed_angles = s * (angles[i]);
        z = z + signed_angles; // Q16.15 - Q16.15 --> Q16.15 result
        
        s = sign(Y_);
    }
    return z;
}

int arctan2(int Y, int X) {
    return cordic_arctan(Y, X);
}
