#include <xc.h>
#include <stdint.h>
#include "ccp_CCP1.h"
#include "LED.h"
#include "tmr_TMR1.h"
#include "Interrupts.h"

uint16_t seconds = 0;
uint16_t delay = 0;

void ccp_CCP1Init(void){

    //Set to compare mode, toggle output on match (not used) clear TMR1
    CCP1CONbits.MODE = 0x01;
  
    
    //Load 31250 = 0x7A12 into CCPR
    CCPR1H = 0x7A;
    CCPR1L = 0x12;
    
    //Enable CCP1 match interrupt
    P_IE = 1;
    G_IE = 1;
    CCP_IE = 1;

  
}

void ccp_CCP1En(void){
    CCP1CONbits.CCP1EN = 1;
}

void ccp_CCP1Dis(void){
    CCP1CONbits.CCP1EN = 0;
}

void ccp_CCP1CompareMatch(void){
    //LEDLAT ^=1;
    /*
    seconds++;
    if (seconds == delay){
        tmr_TMR1Dis();
        ccp_CCP1Dis();
        LEDLAT = 0;   
    }
    */
}

void ccp_CCP1CompareReset(void){
    seconds = 0;
}

void ccp_CCP1SetDelay(uint16_t newDelay){
    delay = newDelay;
}