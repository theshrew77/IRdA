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
//static uint8_t TMR0rolloverArray [34] = {0};
static uint8_t sample = 0;
static uint8_t accComplete = 0;
/*
char str[6];
char CRLF[4] = "\r\n";

void tmr_TMR0_PrintCountArray(void){
    for (int i = 0; i <34; i++){
        itoa(str,TMR0countArray[i],10);
        Uart_UCA0_puts(str);
        Uart_UCA0_puts(CRLF);
    }
}
*/
uint16_t tmr_computeDelta(uint8_t i){

    //return ((uint8_t)(TMR0countArray[i+1]+(uint16_t)TMR0rolloverArray[i+1]*TMR0MAX - TMR0countArray[i]));
    //return ((TMR0countArray[i+1]+(uint16_t)TMR0rolloverArray[i+1]*TMR0MAX - TMR0countArray[i]));
    return (((uint16_t)TMR0countArray[i+1] - TMR0countArray[i]));
}

uint8_t accquisitionComplete(void){
    return(accComplete);
}

void tmr_TMR0mark(void){
    TMR0countArray[sample] = TMR0L;
    TMR0countArray[sample] += (uint16_t)TMR0H << 8;
    //TMR0rolloverArray[sample] = TMR0rollovers;
    TMR0rollovers = 0;
    sample++;
}

void tmr_TMR0reset(void){
    for (int i = 0; i < 33; i++){
        TMR0countArray[i] = 0;
        //TMR0rolloverArray[i] = 0;
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
    TMR0PRE = 0; //1:1 prescaler
    TMR016BEN = 1; //enable reading timer register in 1 16 bit operation
    TMR0CS = 2;   //select Fosc/4 as clock source
    TMR0H = 0xB8;
    TMR0L = 0x15;
    
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