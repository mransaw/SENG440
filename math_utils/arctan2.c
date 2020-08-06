
#include <diagonalize.h>
#include <linear_approx.h>
#include <stdio.h>
#include <math.h>
#define sign(V) (V >= 0) - (V < 0)

int arctan2(int Y, int X) {
    register int z = 0;
    register int X_ = (X << 14);

    register int Y_ = (Y << 14);
    X_ *= sign(X_);

    Y_ *= sign(Y_);
    register int delta_x = 0;

    register int delta_y = 0;
    register int s = sign(Y_);

    for (int i = 0; i < ITER; ++i) {
        delta_x = s * (Y_ >> i);
        delta_y = -s * (X_ >> i);

        X_ = X_ + delta_x;
        Y_ = Y_ + delta_y;

        z = z + (s * (angles[i]));
        s = sign(Y_);
    }
    return z;
}