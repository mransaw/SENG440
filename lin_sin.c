#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// assuming input and output are both N-bit signed integers
#define N_BITS 14

int main(void) {
    // calculate points of theta for linear approximation
    int points[3] = {-pow(2,N_BITS-1), 0, pow(2,N_BITS-1)-1};
    
    // calculate slopes of lines
    int slope = 1;
    
    // use if N bits output not equal to N bits input
    //int slope = (N_BITS_OUT) / (N_BITS_IN); 
    
    // calculate y-intercepts of lines
    int y_int = pow(2,N_BITS-2);
   
    int theta, result;
    
    while(1) {
        //assuming theta between -pi and pi
        float theta;
        int result;
        printf("Enter theta: ");
        scanf("%f", &theta);
        
        // scale theta
        theta = theta * pow(2,N_BITS-1) / M_PI;
        
        if (theta < points[1]) {
            printf("Theta is less than: %d\n", points[1]);
            result = slope * theta + y_int;
        } else if (theta < points[2]) {
            printf("Theta is less than: %d\n", points[2]);
            result = -slope * theta + y_int;
        } else {
            printf("WARNING: theta must be between -pi and pi\n");
            return -1;
        }
        
        printf("Result is: %d\n\n", result);
    }    
    
    return 0;
}