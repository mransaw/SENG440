#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "linear_approx.h"

int lin_cos(int theta) {
    int t_theta, result;    
    
    //assumes an input scale factor of (2^31)/pi
    
    // magnitude of slopes is 2/pi, scaled
    
    // magnitude of y-intercepts is 1, scaled
    int y_int = (1<<30);
    
    if (theta < 0) {
        printf("one\n");
        result = theta + y_int;
    } else {
        result = -theta + y_int;
    }
    
    // output scale factor is 2^30
    return result;
}
