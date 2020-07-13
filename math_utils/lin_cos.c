#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "linear_approx.h"

#define Y_INT (1<<SF_ATAN_IN)    // magnitude of y-intercepts is 1, scaled

int16_t lin_cos(int16_t theta) {
    int16_t result;    
    
    if (theta < 0) {
        result = SLOPE_SINCOS * theta + Y_INT;
    } else {
        result = -SLOPE_SINCOS * theta + Y_INT;
    }
    
    return result;
}
