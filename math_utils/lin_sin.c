#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <linear_approx.h>

int lin_sin(int theta) {
    // calculate points of theta for linear approximation
    int points[3] = {-pow(2,N_BITS-1), 0, pow(2,N_BITS-1)-1};
    
    // calculate slopes of lines
    int slope = 1;
    
    // use if N bits output not equal to N bits input
    //int slope = (N_BITS_OUT) / (N_BITS_IN); 
    
    // calculate y-intercepts of lines
    int y_int = pow(2,N_BITS-2);
   
    int result;
    
    if (theta < points[1]) {
        result = slope * theta + y_int;
    } else if (theta < points[2]) {
        result = -slope * theta + y_int;
    } else {
        assert(0);
    }
    
    return result;
}