#include <xc.h>
#include "Oscillator.h"

void osc_Config16MHz(void){
        
    OSCFRQ = 0b0000101;    //set high frequency internal oscillator to 16MHz
    OSCCON1 = 0b01100000; //set clock tree to take High frequency internal oscillator with 1:1 prescaler
}

void _osc_Config32768Hz(void){
    while(!OSCSTATbits.EXTOR); //wait for the external oscillator to be ready
    OSCENbits.EXTOEN = 1;       //explicitly enable external osciallator
    OSCCON1 = 0b01110000;       //set clock tree to accept external oscillator with 1:1 prescaler
    while(!OSCCON3bits.ORDY);   //wait for the oscillator to be ready
}
