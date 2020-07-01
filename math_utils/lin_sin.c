#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "linear_approx.h"

int lin_sin(int theta) {
    int t_theta, result;    
    
    // (assumes an input scale factor of (2^31)/pi

    // calculate bounds for theta
    int points[2] = {-(1<<30), (1<<30)};
    
    // magnitude of slopes is 2/pi, scaled

    // magnitude of y-intercepts is 2, scaled
    int y_int = 0x7FFFFFFF;
    
    if (theta < points[0]) {
        result = -theta - y_int;
    } else if (theta < points[1]) {
        result = theta;
    } else {
        result = -theta + y_int;
    }
    
    // output scale factor is 2^30
    return result;
}
