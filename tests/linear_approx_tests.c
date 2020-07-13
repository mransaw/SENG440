#include <linear_approx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int UPPER_BOUND = 1 << SF_ATAN_IN;
static double test_vector[NPOINTS];
static int test_vector_scaled[NPOINTS];

void arctan_tests() {
    // max input magnitude is 2^31
    int min_input = -8192,
        max_input = 8192;
    double x;
    double r1;
    double r2;
    for (int X = min_input; X <= max_input; ++X) {
        x = ((double)X) / ((double)(1 << SF_ATAN_IN));
        r1 = atan(x);
        r2 = ((double)(arctan(X) * ((double)M_PI))) / ((double)(1 << SF_ATAN_OUT)) / ((double)(1 << SF_ATAN_OUT));
        printf("atan(x = %f) = %f, arctan(X = %d) * M_PI/ (2^14) = %f, error = %f\n", x, r1, X, r2, fabs(r1 - r2));
    }
}

void arctan_tests_int(void) {
    /*int min_element = -8192,
        max_element = 8192;
    // ^^^ above is only true for the first iteration of sweep 1 ^^^ */
    
    // max unscaled value of matrix elements is (2^31)/(2^SF_ATAN_IN)
    int min_element = -(1 << (32-SF_ATAN_IN)),
        max_element = 1 << (32-SF_ATAN_IN);   
       
    // max input magnitude is 2^31
    int min_input = 0x80000000,
        max_input = 0x7FFFFFFF;
        
    printf("input to arctan(): min is %d, max is %d\n", min_input, max_input);
    
    // test minimum input
    int output = arctan(min_input); // function being tested
    double actual = atan2(min_element,1);
    int want = actual / M_PI * pow(2,SF_ATAN_OUT);    //-pi/2, scaled
    
    printf("input: %d, output = %d, wanted: %d\n", min_input, output, want);
    
    double error = fabs((double)(output - want)/want) * 100;
    printf("percent error is %f\n", error);
     
    if (error > MAX_ERROR_ATAN) {
        printf("integer arctan test failed for minimum input\n");   
        return;      
    }
    
    // test maximum input
    output = arctan(max_input); // function being tested
    actual = atan2(max_element,1);
    want = actual / M_PI * pow(2,SF_ATAN_OUT);    //pi/2, scaled
    
    printf("input: %d, output = %d, wanted: %d\n", max_input, output, want);
        
    error = fabs((double)(output - want)/want) * 100;
    printf("percent error is %f\n", error);
        
    if (error > MAX_ERROR_ATAN) {
        printf("integer arctan test failed for maximum input\n");         
        return;
    }
    
    int nloops = 500,
        range = 5;
    for (int i=0; i<nloops; i++) {
        double loopf = 2 * (double)i/(nloops) - 1;
        //printf("loopf is: %f\n", loopf);
        // regular test vector
        //test_vector[i] = M_PI*loopf;
        int scaled_input = loopf * (range << SF_ATAN_IN);
        output = arctan(scaled_input);    // function being tested
        // test vector from -pi to pi, scaled
        //test_vector_scaled[i] = loopf*pow(2,SF_ATAN_IN);
        double input = loopf * range;
        actual = atan(input);
        want = actual / M_PI * pow(2,SF_ATAN_OUT);
        
        printf("\ninput: %d(%f), output = %d, wanted: %d(%f)\n", scaled_input, input, output, want, actual);
        
        error = fabs((double)(output - want)/want) * 100;
        printf("percent error is %f\n", error);
            
        if (error > MAX_ERROR_ATAN) {
            printf("integer arctan test failed for input: %d(%f rads)\n\n", scaled_input, input);         
            return;
        }
        
    }
    
    printf("integer arctan test passed\n");
    return;
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

int main(void) {
    //generate_arctan_table_output();
    arctan_tests();
   //printf("---------\n");
   arctan_tests_int();
    //printf("---------\n");
 //   
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
