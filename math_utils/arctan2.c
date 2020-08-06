
#include <diagonalize.h>
#include <linear_approx.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int arctan2(int Y, int X) {
    clock_t clk = clock();
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
            z = z + angles[i];
        } else {
            delta_x = - (Y_ >> i);
            delta_y = + (X_ >> i);
            X_ = X_ + delta_x;
            Y_ = Y_ + delta_y;
            z = z - angles[i];
        }
    }
    clk = clock() - clk;
    printf("arctan computation time: %lu\n", clk);
    return z;
}
