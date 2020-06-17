#include <xc.h>
#include <stdint.h>
#include "LED.h"
#include "main.h"

static uint8_t LED_status = OFF;

void led_ConfigureLED(void){
    LED1TRIS = 0;
    LED1LAT  = 1;
    LED2TRIS = 0;
    LED2LAT  = 1;
}

void led_Bright(void){
    LED1LAT = 0;
    LED2TRIS = 0;
    LED2LAT = 0;
    LED_status = ON;
}

void led_Dim(void){
    LED1LAT = 0;
    LED2TRIS = 1;
    LED_status = ON;
}

void led_Off(void){
    LED1LAT = 1;
    LED2TRIS = 0;
    LED2LAT = 1;
    LED_status = OFF;
}

void led_Toggle(void){
    if (LED_status == ON){
        led_Off();
    }
    else
       led_Bright();     
}

