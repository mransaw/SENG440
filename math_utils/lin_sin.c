#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdint.h>
#include "linear_approx.h"

#define Y_INT (1<<(1+SF_ATAN_IN))    // magnitude of y-intercepts is 2, scaled
#define LOW_POINT -(1<<(SF_ATAN_OUT-1))  // common points of approximation are pi/2 and -pi/2, scaled
#define HIGH_POINT (1<<(SF_ATAN_OUT-1))

int16_t lin_sin(int16_t theta)
{
    int16_t result;    
    
    if (theta < LOW_POINT) {
        result = -SLOPE_SINCOS * theta - Y_INT;
    } else if (theta < HIGH_POINT) {
        result = SLOPE_SINCOS * theta;
    } else {
        result = -SLOPE_SINCOS * theta + Y_INT;
    }
    
    return result;
}
