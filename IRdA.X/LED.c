#include <xc.h>
#include <stdint.h>
#include "LED.h"
#include "main.h"

void led_ConfigureLED(void){
    LEDTRIS = 0;
    LEDLAT  = 0;
}

void led_Blink(uint8_t times){
    for (int i = 0; i < times; i++){
        LEDLAT ^= 1;
        __delay_ms(500);
        LEDLAT ^= 1;
        __delay_ms(500);
    }
}
