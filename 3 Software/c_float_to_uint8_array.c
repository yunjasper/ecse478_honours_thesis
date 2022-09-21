#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

union myf {
    float f;
    uint8_t bytes[8];
};

int main() {
    
    union myf f_u;

    for (uint8_t i = 0; i < 128; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            f_u.bytes[j] = i;
        }

        printf("EoF = %d, f = %f\r\n", i, f_u.f);
    }

    // todo: test on STM32 and check the value of f

}