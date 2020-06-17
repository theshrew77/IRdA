#include <xc.h>
#include "Oscillator.h"



void osc_Config1MHz(void){
        
    OSCFRQ = 0b0000000;    //set high frequency internal oscillator to 16MHz
    OSCCON1 = 0b01100000; //set clock tree to take High frequency internal oscillator with 1:1 prescaler
}


