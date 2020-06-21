#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char* method;
    int32_t result = 5000/3;
    if (result == 1667) {
        method = "round to nearest LSB";
    } else {
        method = "truncate";
    }
        
    printf("Rounding method: %s (%d)\n", method, result);
    
    int edge = 0x7FFFFFFF;
    result = edge + 0xFFFF;
    
    if (result < 0) {
        method = "overflow";
    } else {
        method = "saturation";
    }
    
    printf("Addition overflow results in: %s (%d)\n", method, result);

    result = (int16_t)0x4000 * (int16_t)0x4000;
    
    printf("0x4000 ^ 2 = 0x%x\n", result);

    return 0;
}
