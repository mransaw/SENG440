#include <linear_approx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NPOINTS 300

#define SF_IN 14   // input scale factor for arctan() is 2^SF_IN
#define SF_OUT 14  // output scale factor for arctan() is (2^SF_OUT)/pi 
#define MAX_ERROR_ATAN 10   // arctan maximum error in %

int UPPER_BOUND = 1 << SF_IN;
static double test_vector[NPOINTS];
static int test_vector_scaled[NPOINTS];

void arctan_tests_int(void) {
    int min_element = -8192,
        max_element = 8192;
    
    int min_input = (min_element/1) << SF_IN,
        max_input = (max_element/1) << SF_IN;
        
    printf("input to arctan(): min is %d, max is %d\n", min_input, max_input);
    
    // test minimum input
    int output = arctan(min_input); // function being tested
    double actual = atan2(min_element,1);
    int want = actual / M_PI * pow(2,SF_OUT);    //-pi/2, scaled
    
    printf("output = %d, wanted: %d\n", output, want);
    
    double error = fabs((double)(output - want)/want) * 100;
    printf("percent error is %f\n", error);
     
    if (error > MAX_ERROR_ATAN) {
        printf("integer arctan test failed for minimum input\n");   
        return;      
    }
    
    // test maximum input
    output = arctan(max_input); // function being tested
    actual = atan2(max_element,1);
    want = actual / M_PI * pow(2,SF_OUT);    //pi/2, scaled
    
    printf("output = %d, wanted: %d\n", output, want);
        
    error = fabs((double)(output - want)/want) * 100;
    printf("percent error is %f\n", error);
        
    if (error > MAX_ERROR_ATAN) {
        printf("integer arctan test failed for maximum input\n");         
        return;
    }
    
    printf("integer arctan test passed\n");
    return;
}

void arctan_tests() {
    double theta = -1.0;
    double max_error = 0;
    while (theta <= 0.99) {
        theta += 0.01;
        double r1 = atan(theta);
        int X = theta * UPPER_BOUND;
        double linear_approx_value = (arctan(X) * M_PI) / pow(2, 14);
        printf("x = %f\n", theta);
        printf("linear approx arctan = %f\n", linear_approx_value);
        printf("atan() = %f\n", r1);
        int result = linear_approx_value;
        printf("----------------\n");
        if (fabs(result - r1) > max_error) {
            max_error = fabs(result - r1);
        }
    }
    printf("\n\nARCTAN MAX ERROR: %f\n\n\n", max_error);
}

void lin_cos_tests() {
    double error,
           total_error = 0,
           max_error = 0,
           max_error_angle=0;    
    for (int i=0; i<NPOINTS; i++) {
        error = fabs(((lin_cos(test_vector_scaled[i]) + (1<<29)) >> 30) - cos(test_vector[i]));
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
        error = fabs(((lin_sin(test_vector_scaled[i]) + (1<<29)) >> 30) - sin(test_vector[i]));
        //printf("error: %f\n", error);
        total_error += error;
        if (error > max_error) {
            max_error = error;
            max_error_angle = test_vector[i];
        }
    }
    
    printf("lin_sin max error: %f at %f rads, avg error: %f\n", max_error, max_error_angle, total_error/NPOINTS);
}

int main(void) {
    //generate_arctan_table_output();
    //arctan_tests();
   //printf("---------\n");
   arctan_tests_int();
 //   printf("---------\n");
 //   
 //   // generate test vectors for sin/cos
 //   for (int i=0; i<NPOINTS; i++) {
 //       double loopf = 2 * (double)i/(NPOINTS) - 1;
 //       //printf("loopf is: %f\n", loopf);
 //       // regular test vector
 //       test_vector[i] = M_PI*loopf;
 //       // test vector from -pi to pi, scaled
 //       test_vector_scaled[i] = (unsigned int)(1<<31)*loopf;
 //       //printf("test vector: %f, scaled: %d\n", test_vector[i], test_vector_scaled[i]);
 //   }  
//
 //   // run sin/cos tests
 //   lin_cos_tests();
 //   printf("---------\n");
 //   lin_sin_tests();
 //   //printf("---------\n");
 //   return 0;
}
