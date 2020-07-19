#include <stdint.h>

#ifndef N_BITS
#define N_BITS 15
int divide_by_subraction(int Y, int X);
void generate_angles_table();
void d_generate_angles_table();
double d_arctan2(double y, double x);
int arctan2(int Y, int X);
int int_arctan(int X);
void basic_linear_approximation();
void generate_linear_approximation();
int arctan(int x);
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
