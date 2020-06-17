#include <xc.h>
#include <stdint.h>
#include "main.h"
#include "tmr_TMR0.h"
#include "tmr_TMR1.h"
#include "Interrupts.h"
#include "LED.h"
#include "RTC.h"
//#include <stdio.h>

extern uint8_t IR_received;
extern uint8_t TMR1IntType;

void configureIOCInt(void){
    //enable interrupt on change
    IOC_IE = 1;
    //enable global interrupts
    G_IE = 1;
    
    //enable IOCA4 for negative edge detection
    IOCA_N = 1;
    IOCA_TRIS = 1;
    IOCA_ANSEL = 0; 

    

}


__interrupt() void ISR(void){
   
    
    if(IOC_IF){                 //check if IOC is interrupt source
        IR_received = 1;        //if it is mark that IR is received to make the main while(1) wait until the full command is received and not go back to sleep
        IOCA_F = 0;             //clear the pin specific IOC flag. This must be done before clearing the general IOC flag
        IOC_IF = 0;             //clear the general IOC flag
        if (!TMR0_ON) {         //If timer 0 is not on, preload it and start. The preload makes it time out shortly after a full NEC packet is received
            TMR0H = TMR0_PLH;   //see timr_TMR0.h
            TMR0L = TMR0_PLL;
            TMR0_ON = 1;        //start the timer
        }
        tmr_TMR0mark();         //mark the time an IOC interrupt occured. These marked times are used to decode the NEC packet
        
    }
    
    if(TMR1IFG){                        //check if timer 1 is the interrupt source
        TMR1IFG = 0;                    //clear timer 1 interrupt flag
        tmr_TMR1Reset();                //reset timer 1. This includes a preload designed to make the timer roll over at 1 second and 0.01 seconds with 32.768KHz clock source
        if (TMR1IntType == INT_DELAY){  //if the interrupt type has been set to delay, service the RTC
            
            rtc_ISR();
        }
        if (TMR1IntType == INT_CANDLE){ //if the interrupt time has been set to candle, toggle the LED
            
            led_Toggle();
        }
    }
    
    if (TMR0IFG){                       //check if timer 0 is the interrupt source. This occurs when it times our from receiving an NEC packet
        TMR0IFG = 0;                    //clear the interrupt flag
        tmr_TMR0IncRollovers();         //increment the rollover count
        
        
    }
    
    return;
}

