#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <linear_approx.h>

int lin_sin(int theta) {
    int t_theta, result;    
    
    // truncate theta (assumes an input scale factor of (2^31)/pi
    t_theta = (theta>>16);
    
    // magnitude of slopes is 2/pi, scaled
    int slope = (1<<16);
    printf("slope = %d\n", slope);
    
    // magnitude of y-intercepts is 1, scaled
    int y_int = (1<<30);
    printf("y-int = %d\n", y_int);
    
    if (theta < 0) {
        result = slope * theta + y_int;
    } else {
        result = -slope * theta + y_int;
    }
    
    // output scale factor is 2^30
    return result;
}
