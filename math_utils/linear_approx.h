#ifndef N_BITS
#define N_BITS 15
int int_arctan(int X);
void basic_linear_approximation();
void generate_linear_approximation();
int arctan(int x);
int lin_sin(int theta);
int lin_cos(int theta);
#endif

#define NPOINTS 300

#define SF_IN 14   // input scale factor for arctan() is 2^SF_IN
#define SF_OUT 14  // output scale factor for arctan() is (2^SF_OUT)/pi 
#define MAX_ERROR_ATAN 10   // arctan maximum error in %

#define SF_ATAN_IN 14      // scale factor is 2^SF_ATAN_IN
#define SF_ATAN_OUT 14      // scale factor is (2^SF_ATAN_OUT)/pi

#define SLOPE_SINCOS (1<<(1+SF_ATAN_OUT - SF_ATAN_IN))    // magnitude of slopes is 2/pi, scaled
