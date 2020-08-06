#include <stdint.h>

#ifndef N_BITS
#define N_BITS 15
int arctan2(int Y, int X);
int arctan2_ver1(int Y, int X);
int16_t lin_sin(int16_t theta);
int16_t lin_cos(int16_t theta);
#endif

#define NPOINTS 300

#define SF_IN 14   // input scale factor for arctan() is 2^SF_IN
#define SF_OUT 14  // output scale factor for arctan() is (2^SF_OUT)/pi 
#define MAX_ERROR_ATAN 10   // arctan maximum error in %

#define SF_ATAN_IN 14      // scale factor is 2^SF_ATAN_IN
#define SF_ATAN_OUT 15     // scale factor is (2^SF_ATAN_OUT) / pi

#define SLOPE_SINCOS (1<<(1+SF_ATAN_OUT - SF_ATAN_IN))    // magnitude of slopes is 2/pi, scaled
