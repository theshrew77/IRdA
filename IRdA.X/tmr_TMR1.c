#include <xc.h>
#include <stdint.h>
//#include <stdio.h>

#include "tmr_TMR1.h"
#include "Interrupts.h"
#include "main.h"

//static uint16_t TMR1rollovers = 0;
//uint16_t TMR1count = 0;
//static uint16_t TMR1countArray [34] = {0};
//static uint16_t TMR1rolloverArray [34] = {0};
//static uint8_t sample = 0;
//static uint8_t accComplete = 0;
static uint16_t TMR1preload = TMR1_1s;

void tmr_TMR1setPreload(uint16_t preload){
    TMR1preload = preload;
}
/*
uint16_t tmr_computeDelta(uint8_t i){
    if (_XTAL_FREQ == 16000000){
        return ((TMR1countArray[i+1]+(uint32_t)TMR1rolloverArray[i+1]*TMR1MAX - TMR1countArray[i])>>4);
    }
    
    if (_XTAL_FREQ == 32768){
        return ((TMR1countArray[i+1]+(uint32_t)TMR1rolloverArray[i+1]*TMR1MAX - TMR1countArray[i]));
    }
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
    
    if ( TMR1rollovers > 0){
        tmr_TMR1Dis();
        accComplete = 1;
    }
    
}
*/

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
    
    //TMR1XTALEN = 0x01;              //enable SOSC as clock source
    
    TMR1IFG = 0;                    //clear TMR1 interrupt flag
    TMR1H = (TMR1preload & 0xFF00) >> 8;// 0x7F;                   //set TMR1 register = 32767 = 0x7FFF
    TMR1L = TMR1preload & 0x00FF;
 
    

    //enable rollover interrupts
    TMR1_IE  = 1;
    P_IE = 1;
    G_IE = 1;
    

    
}

void tmr_TMR1SOSCpowerLevel(char level){
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
    TMR1H = (TMR1preload & 0xFF00) >> 8;// 0x7F;                   //set TMR1 register = 32767 = 0x7FFF
    TMR1L = TMR1preload & 0x00FF;
    TMR1_ON = 1;
}

/*
void tmr_TMR1Toggle(void){

    TMR1_ON ^= 1;
     
}
*/