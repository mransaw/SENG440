#include <linear_approx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int UPPER_BOUND = 1 << SF_ATAN_IN;
static double test_vector[NPOINTS];
static int test_vector_scaled[NPOINTS];

void arctan_tests() {
    // 16-bit floating point input limits
    double min_input = -1 * pow(2, 16);
    double max_input = pow(2, 16) - 1;
    double inc = (max_input - min_input) / 16;
    for (double x = min_input; x < max_input; x += inc) {
        if (x != 0) {
            for (double y = min_input; y < max_input; y += inc) {
                printf("y = %f, x = %f\n", y, x);
                int Y = y * pow(2, SF_ATAN_IN);
                int X = x * pow(2, SF_ATAN_IN);
                int scaled_result = arctan2(Y, X);
                double unscaled_result = ((double)scaled_result) * M_PI / pow(2, SF_ATAN_OUT);
                double result = unscaled_result;
                double expected = atan(y/x) / M_PI;
                double error_percent = 100 * (result - expected) / expected;
                if (error_percent > 10) {
                    printf("our result: %f\n expected result: %f\n percent error: %f\n----------------------\n", result, expected, error_percent);
                }
            }
        }
    }
}

void lin_cos_tests() {
    double error,
           total_error = 0,
           max_error = 0,
           max_error_angle=0;    
    for (int i=0; i<NPOINTS; i++) {
        error = fabs(((lin_cos(test_vector_scaled[i]) + (1<<(SF_ATAN_IN-1))) >> SF_ATAN_IN) - cos(test_vector[i]));
        total_error += error;
        if (error > max_error) {
            max_error = error;
            max_error_angle = test_vector[i];
        }
    }
    
    printf("lin_cos max error: %f at %f rads, avg error: %f\n", max_error, max_error_angle, total_error/NPOINTS);
}

void lin_sin_tests() {
    double error,
           total_error = 0,
           max_error = 0,
           max_error_angle=0;    
    for (int i=0; i<NPOINTS; i++) {
        error = fabs(((lin_sin(test_vector_scaled[i]) + (1<<(SF_ATAN_IN-1))) >> SF_ATAN_IN) - sin(test_vector[i]));
        //printf("error: %f\n", error);
        total_error += error;
        if (error > max_error) {
            max_error = error;
            max_error_angle = test_vector[i];
        }
    }
    
    printf("lin_sin max error: %f at %f rads, avg error: %f\n", max_error, max_error_angle, total_error/NPOINTS);
}

int main() {
    //int n = 2;
    //int d = 5; 
    //int div = divide_by_multiply(n << SF_ATAN_IN, d << SF_ATAN_IN);
    //printf("div = %d, expected = %f\n", div, ((double)n) / ((double)d));
    arctan_tests();
   
    // generate test vectors for sin/cos
   /* for (int i=0; i<NPOINTS; i++) {
        double loopf = 2 * (double)i/(NPOINTS) - 1;
        //printf("loopf is: %f\n", loopf);
        // regular test vector
        test_vector[i] = M_PI*loopf;
        // test vector from -pi to pi, scaled
        test_vector_scaled[i] = loopf*pow(2,SF_ATAN_OUT);
        //printf("test vector: %f, scaled: %d\n", test_vector[i], test_vector_scaled[i]);
    }  */
//
 //   // run sin/cos tests
 //   lin_cos_tests();
   // printf("---------\n");
   // lin_sin_tests();
 //   //printf("---------\n");
    //return 0;
}
