#include <linear_approx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int UPPER_BOUND = 1 << SF_ATAN_IN;
static double test_vector[NPOINTS];
static int test_vector_scaled[NPOINTS];

void arctan_tests() {
    // 16-bit floating point input limits, for quadrants I and IV only (quadrants II and III are unnecessary in Jacobi method)
    double min_x = 0;
    double max_x = pow(2, 16 - 1) - 1;
    double min_y = -pow(2, 16 - 1);
    double max_y = pow(2, 16 - 1) - 1;
    double x_inc = (max_x - min_x) / 16;
    double y_inc = (max_y - min_y) / 16;

    for (double x = min_x; x < max_x; x += x_inc) {
        if (x != 0) {
            for (double y = min_y; y < max_y; y += y_inc) {
                int Y = y * pow(2, SF_ATAN_IN);
                int X = x * pow(2, SF_ATAN_IN);
                printf("Y = %d, X = %d\n", Y, X);
                double result = ((double)arctan2(Y, X)) / pow(2, SF_ATAN_OUT);
                double expected = (atan(y/x));
                double error_percent = 100 * ((result - expected) / expected);
                if (fabs(error_percent) > 10 && fabs(result - expected) > 0.001) {
                    printf("        TEST FAIL\n----------------------\n");
                }
                printf("y = %f, x = %f, y/x = %f, \n      our unscaled result: %f\n expected unscaled result: %f\n percent error: %f\n------------------\n", y, x, y/x, (double)result, expected, error_percent);
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
    //int n = -3;
    //int d = 2; 
    //int div = divide_by_subraction(n << SF_ATAN_IN, d << SF_ATAN_IN);
    //int expected = (int)((n << SF_ATAN_IN) / d);
    //printf("div = %d, expected = %d\n", div, expected);
    //generate_linear_approximation(-1.0, 1.0, 0.1);
    arctan_tests();
   
 /*   // generate test vectors for sin/cos
    for (int i=0; i<NPOINTS; i++) {
        double loopf = 2 * (double)i/(NPOINTS) - 1;
        //printf("loopf is: %f\n", loopf);
        // regular test vector
        test_vector[i] = M_PI*loopf;
        // test vector from -pi to pi, scaled
        test_vector_scaled[i] = loopf*pow(2,SF_ATAN_OUT);
        //printf("test vector: %f, scaled: %d\n", test_vector[i], test_vector_scaled[i]);
    }  
//
 //   // run sin/cos tests
   lin_cos_tests();
    printf("---------\n");
    lin_sin_tests();*/
 //   //printf("---------\n");
    //return 0;
}
