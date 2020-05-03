#include <pic16lf15313.h>
#include <stdint.h>
//#include <stdio.h>

#include "tmr_TMR1.h"
#include "Interrupts.h"

static uint16_t TMR1rollovers = 0;
uint16_t TMR1count = 0;
static uint16_t TMR1countArray [34] = {0};
static uint16_t TMR1rolloverArray [34] = {0};
static uint8_t sample = 0;
static uint8_t accComplete = 0;

uint16_t computeDelta(uint8_t i){
    return ((TMR1countArray[i+1]+(uint32_t)TMR1rolloverArray[i+1]*TMR1MAX - TMR1countArray[i])>>4);
}

uint16_t *getTMR1countArray(void){
    return(TMR1countArray);
}

uint16_t *getTMR1rolloverArray(void){
    return(TMR1rolloverArray);
}

uint8_t accquisitionComplete(void){
    return(accComplete);
}

void tmr_TMR1mark(void){
    TMR1countArray[sample] = TMR1;
    TMR1rolloverArray[sample] = TMR1rollovers;
    TMR1rollovers = 0;
    sample++;
}

void tmr_TMR1reset(void){
    for (int i = 0; i < 33; i++){
        TMR1countArray[i] = 0;
        TMR1rolloverArray[i] = 0;
    }
    sample = 0;
    accComplete = 0;
}

uint32_t tmr_TMR1GetCount(){
    uint32_t TMR1TotalCount = TMR1;
    TMR1TotalCount = TMR1TotalCount + (uint32_t)TMR1rollovers*TMR1MAX;
    //printf("rollovers = %e\r\n",524280);
    //printf("rollovers*65535 = %u\r\n",TMR1rollovers*65535);
    return(TMR1TotalCount);
}

uint16_t *tmr_TMR1GetRollovers(void){
    return(&TMR1rollovers);
}

void tmr_TMR1ClrRollovers(void){
    TMR1rollovers = 0;
}

void tmr_TMR1IncRollovers(void){
    TMR1rollovers++;
    
    if ( TMR1rollovers > 4){
        tmr_TMR1Dis();
        accComplete = 1;
    }
    
}

void tmr_TMR1Init(void){
    TMR1PRE = 0; //1:1 prescaler
    TMR116BEN = 1; //enable reading timer register in 1 16 bit operation
    TMR1CS = 2;   //select Fosc as clock source
    
    //enable rollover interrupts
    TMR1_IE  = 1;
    P_IE = 1;
    G_IE = 1;
    
    //calculate timer 1 max microseconds
    //TMR1Max = TMR1MAX / _XTAL_FREQ

    
}

void tmr_TMR1En(void){
    //turn timer on
    TMR1_ON = 1;
   
}

void tmr_TMR1Dis(void){
    //turn timer off
    TMR1_ON = 0;
}


void tmr_TMR1Toggle(void){

    TMR1_ON ^= 1;
     
}
