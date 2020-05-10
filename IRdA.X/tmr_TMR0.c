#include <xc.h>
#include <stdint.h>
#include "tmr_TMR0.h"
#include "Interrupts.h"
#include "main.h"

static uint8_t TMR0rollovers = 0;
uint8_t TMR0count = 0;
static uint8_t TMR0countArray [34] = {0};
static uint8_t TMR0rolloverArray [34] = {0};
static uint8_t sample = 0;
static uint8_t accComplete = 0;

uint8_t tmr_computeDelta(uint8_t i){

    return ((uint8_t)(TMR0countArray[i+1]+(uint16_t)TMR0rolloverArray[i+1]*TMR0MAX - TMR0countArray[i]));
   
}

uint8_t accquisitionComplete(void){
    return(accComplete);
}

void tmr_TMR0mark(void){
    TMR0countArray[sample] = TMR0L;
    TMR0rolloverArray[sample] = TMR0rollovers;
    TMR0rollovers = 0;
    sample++;
}

void tmr_TMR0reset(void){
    for (int i = 0; i < 33; i++){
        TMR0countArray[i] = 0;
        TMR0rolloverArray[i] = 0;
    }
    sample = 0;
    accComplete = 0;
}

void tmr_TMR0IncRollovers(void){
    TMR0rollovers++;
    
    if ( TMR0rollovers > 1){
        tmr_TMR0Dis();
        accComplete = 1;
    }
    
}

void tmr_TMR0Init(void){
    TMR0PRE = 0; //1:1 prescaler
    TMR016BEN = 0; //enable reading timer register in 1 16 bit operation
    TMR0CS = 2;   //select Fosc/4 as clock source
    
    //enable rollover interrupts
    TMR0_IE  = 1;
    P_IE = 1;
    G_IE = 1;
    
    //calculate timer 1 max microseconds
    //TMR1Max = TMR1MAX / _XTAL_FREQ

    
}

void tmr_TMR0Dis(void){
    //turn timer off
    TMR0_ON = 0;
}