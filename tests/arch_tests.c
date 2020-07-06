#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char* method;
    int32_t result;
    float fresult = 5000.0/3.0;
        
    printf("Rounding method: 5000 / 3 = (%f)\n", method, fresult);
    
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
