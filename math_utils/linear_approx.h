#ifndef N_BITS
#define N_BITS 15
double d_arctan(double x);
void generate_linear_approximation();
int arctan(int x);
int lin_sin(int theta);
int lin_cos(int theta);
#endif

#define SF_ATAN_IN 14       // scale factor is 2^SF_ATAN_IN
#define SF_ATAN_OUT 14      // scale factor is (2^SF_ATAN_OUT)/pi

#define SLOPE_SINCOS (1<<(1+SF_ATAN_IN-SF_ATAN_OUT))    // magnitude of slopes is 2/pi, scaled
