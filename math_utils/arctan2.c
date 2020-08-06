
#include <diagonalize.h>
#include <linear_approx.h>
#include <stdio.h>
#include <math.h>
#define sign(V) (V >= 0) - (V < 0)

void f1() {
    register int z = 0;
}
void f2() {
    int X = 1;
    register int X_ = (X << 14);
}
void f3() {
    int Y = 1;
    register int Y_ = (Y << 14);
}
void f4() {
    int X_ =1;
    X_ *= sign(X_);
}
void f5() {
    int s, Y_, i = 1;
    int delta_x = s * (Y_ >> i);
}
void f6() {
    int X_, delta_x = 1;
    X_ = X_ + delta_x;
}
void f7() {
    int Y_, X_, s = 1, delta_x, delta_y, z = 1;
}
void f8() {
    int s, i = 1;
    int z = z + (s * (angles[i]));
}
void f9() {
    int Y_, X_, s = 1, delta_x, delta_y, z = 1;

    for (int i = 0; i < ITER; ++i) {
        delta_x = s * (Y_ >> i);
        delta_y = -s * (X_ >> i);

        X_ = X_ + delta_x;
        Y_ = Y_ + delta_y;

        z = z + (s * (angles[i]));
        s = sign(Y_);
    }
}

int arctan2(int Y, int X) {
    f1();
    f2();
    f3();
    f4();
    f5();
    f6();
    f7();

    register int z = 0;
    register int X_ = (X << 14);

    register int Y_ = (Y << 14);

    Y_ *= sign(X_);
    X_ *= sign(X_);

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