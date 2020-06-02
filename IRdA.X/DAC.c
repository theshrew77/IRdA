#include <xc.h>
#include <stdint.h>
#include "DAC.h"

static uint8_t DAClevel = 0;

void dac_DACInit(void){
    DAC_EN      = 0x00;     //disable DAC 
    DAC_OE      = 0x00;     //disable DAC output  
    DAC_VP_SEL  = 0x00;     //set V+ to Vdd
    DAC_VN_SEL  = 0x00;     //set V- to Vss
}

void dac_DACEn(void){
    DAC_EN = 0x01;
    DAC_OE = 0x01;
}

void dac_DACDis(void){
    DAC_EN      = 0x00;     //disable DAC 
    DAC_OE      = 0x00;     //disable DAC output 
}

void dac_DAClevelChange(char direction){
    switch (direction){
        case 'u':
            if(DAClevel > DAC_MIN) DAClevel -=7;
            break;
        case 'd':
            if(DAClevel < DAC_MAX) DAClevel += 7;
            break;
    }
    DACCON1bits.DAC1R = DAClevel;
    
    
}
