#include <xc.h>
#include <stdint.h>
#include "LED.h"
#include "main.h"

static uint8_t LED_status = OFF;
/*
 LEDs are controlled via an N channel MOSFET so the LED
 * is on when the pin output is on.
 * TO DO: add second circuit with higher CLR for DIM mode
 */

void led_ConfigureLED(void){
    
    //ODCONAbits.ODCA2 = 1;
    
    //set both LED pins as outputs and high
    LED1TRIS = 0;
    LED1LAT  = 1;
    LED2TRIS = 0;
    LED2LAT  = 1;
}

void led_Bright(void){
    //set LED pin 1 output high
    LED1LAT = 1;
    //set LED pin 2 output low
    LED2LAT = 0;
    LED_status = ON;
}

void led_Dim(void){
    //set LED pin 1 output low
    LED1LAT = 0;
    //set LED pin 2 output high
    LED2LAT = 1;
    LED_status = ON;
}

void led_Off(void){
    //set LED pin 1 output low
    LED1LAT = 0;
    //set LED pin 2 output low
    LED2LAT = 0;
    LED_status = OFF;
}

void led_Toggle(void){
    if (LED_status == ON){
        led_Off();
    }
    else
       led_Bright();     
}

void led_Ack(void){
    if (LED_status == ON){
        led_Off();
        __delay_ms(100);
        led_Bright();
    }
    
    
}

