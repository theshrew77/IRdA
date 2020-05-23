#include <xc.h>
#include "ccp_CCP1.h"



void ccp_CCP1Init(void){
    //Load 31250 = 0x7A12 into CCPR
    CCPR1H = 0x7A;
    CCPR1L = 0x12;
    
    //Set to compare mode, toggle output on match (not used) clear TMR1
    CCP1CONbits.MODE = 0x01;
  
}

void ccp_CCP1En(void){
    CCP1CONbits.CCP1EN = 1;
}

void ccp_CCP1Dis(void){
    CCP1CONbits.CCP1EN = 0;
}

void ccp_CCP1CompareMatch(void){
    
}
