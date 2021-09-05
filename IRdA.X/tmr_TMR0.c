#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "tmr_TMR0.h"
#include "Interrupts.h"
#include "main.h"
#include "NEC.h"
#include "uart_UCA0.h"

static uint8_t TMR0rollovers = 0;
uint8_t TMR0count = 0;
static uint16_t TMR0countArray [34] = {0};
static uint8_t sample = 0;
static uint8_t accComplete = 0;

uint16_t tmr_computeDelta(uint8_t i){

    return (((uint16_t)TMR0countArray[i+1] - TMR0countArray[i]));
}

uint8_t accquisitionComplete(void){
    return(accComplete);
}

void tmr_TMR0mark(void){
    TMR0countArray[sample] = TMR0L;
    TMR0countArray[sample] += (uint16_t)TMR0H << 8;
    TMR0rollovers = 0;
    sample++;
}

void tmr_TMR0reset(void){
    for (uint8_t i = 0; i < 33; i++){
        TMR0countArray[i] = 0;
    }
    sample = 0;
    accComplete = 0;
}

void tmr_TMR0IncRollovers(void){
    TMR0rollovers++;
    
    if ( TMR0rollovers > NEC_TIMEOUT){
        tmr_TMR0Dis();
        accComplete = 1;
    }
    
}

void tmr_TMR0Init(void){
    TMR0PRE = 0;        //1:1 prescaler
    TMR016BEN = 1;      //enable reading timer register in 1 16 bit operation
    TMR0CS = 2;         //select Fosc/4 as clock source
    TMR0H = TMR0_PLH;   //see tmr_TMR0.h for discussion of these values 
    TMR0L = TMR0_PLH;
    
    //enable rollover interrupts
    TMR0_IE  = 1;
    P_IE = 1;
    G_IE = 1;
    
    
}

void tmr_TMR0Dis(void){
    //turn timer off
    TMR0_ON = 0;
}