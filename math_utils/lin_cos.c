#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <linear_approx.h>

int lin_cos(int theta) {
    int t_theta, result;    
    
    // truncate theta (assumes an input scale factor of (2^31)/pi
    t_theta = (theta>>16);
    printf("truncated theta = %d\n", t_theta);

    // calculate bounds for theta
    int points[2] = {-(1<<14), (1<<14)};
    
    // magnitude of slopes is 2/pi, scaled
    int slope = (1<<16);
    printf("slope = %d\n", slope);
    
    // magnitude of y-intercepts is 2, scaled
    int y_int = (2<<30)-1;
    printf("y-int = %d\n", y_int);
    
    if (theta < points[0]) {
        result = -slope * t_theta - y_int;
    } else if (theta < points[1]) {
        result = slope * t_theta;
    } else {
        result = -slope * t_theta + y_int;
    }
    
    // output scale factor is 2^30
    return result;
}
