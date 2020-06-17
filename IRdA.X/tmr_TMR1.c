#include <xc.h>
#include <stdint.h>
//#include <stdio.h>

#include "tmr_TMR1.h"
#include "Interrupts.h"
#include "main.h"

static uint16_t TMR1preload = TMR1_1s;

void tmr_TMR1setPreload(uint16_t preload){
    TMR1preload = preload;
}


void tmr_TMR1Init(void){
    //setup timer 1 to provide 1 second tick to facilitate hour timers
    
    //with Fosc setup as 1MHz, clock source to timer 1 = Fosc/4
    //prescaler 1:8 will reach 1 second every 31250 counts:
    //31250*1/(1000000/(8*4)) = 1
    
    //with LFINTOSC setup as 31KHz, clock source to timer 1 = LFINTOSC
    //prescaler 1:8 will reach 1 second every 31250 counts:
    //3875*1/(31000/(8)) = 1
    
    //with 32.768KHz external crystal, clock source set to OSCI
    //prescaler 1:8 will reach 1 second every 4096 counts:
    //4096*1/(32768/8)= 1
    
     //with 32.768KHz external crystal, clock source set to OSCI
    //prescaler 1:1 will reach 1 second every 32768 counts:
    //32768*1/(32768/1)= 1
    //set TMR1 = 32767
    
    
    TMR1PRE = 0x00;                 //1:1 prescaler
    TMR1CS = 0x02;                  //select external clock source
    T1CONbits.T1SYNC = 1;           //put TMR1 in asynchronous mode to enable operation during sleep
    
    OSCCON3bits.SOSCPWR = 0x01;     //set SOSC power level = low
    OSCCON3bits.SOSCBE = 0x00;      //configure secondary oscillator as crystal
    
    
    TMR1IFG = 0;                            //clear TMR1 interrupt flag
    TMR1H = (TMR1preload & 0xFF00) >> 8;    // see tmr_TMR1.h for discussion of these values                  
    TMR1L = TMR1preload & 0x00FF;
 
    

    //enable rollover interrupts
    TMR1_IE  = 1;
    P_IE = 1;
    G_IE = 1;
    

    
}

void tmr_TMR1SOSCpowerLevel(char level){
    /*
     * for the faster interrupts required to strobe the LED in
     * candle mode the crystal driver circuitry needs to be set to high power
     * to wake up fast enough
     */
    
    switch (level){
        case 'h':
            OSCCON3bits.SOSCPWR = 0x01;
            break;
        case 'l':
            OSCCON3bits.SOSCPWR = 0x00;
            break;
        default:
            OSCCON3bits.SOSCPWR = 0x00;
            break;
    }
}

void tmr_TMR1En(void){
    //enable SOSC as clock source
    TMR1XTALEN = 0x01;
    //turn timer on
    TMR1_ON = 1;
   
}

void tmr_TMR1Dis(void){
    //disable SOSC as clock source
    TMR1XTALEN = 0x00;
    //turn timer off
    TMR1_ON = 0;
}

void tmr_TMR1Reset(void){
    TMR1_ON = 0;
    TMR1H = (TMR1preload & 0xFF00) >> 8;
    TMR1L = TMR1preload & 0x00FF;
    TMR1_ON = 1;
}

