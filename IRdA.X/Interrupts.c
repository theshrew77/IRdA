#include <xc.h>
#include <stdint.h>
#include "main.h"
#include "uart_UCA0.h"
#include "tmr_TMR0.h"
#include "tmr_TMR1.h"
#include "Interrupts.h"
#include "LED.h"
#include "ccp_CCP1.h"
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

    
    //IOCAPbits.IOCAP4 = 1;
}


__interrupt() void ISR(void){
   
    
    if(IOC_IF){
        IR_received = 1;
        IOCA_F = 0; //YOU MUST CLEAR THE PIN SPECIFIC INTERRUPT FIRST 
        IOC_IF = 0;
        if (!TMR0_ON) {
            TMR0H = TMR0_PLH;
            TMR0L = TMR0_PLL;
            TMR0_ON = 1;
        }
        //LEDLAT ^= 1;
        tmr_TMR0mark();
        
    }
    
    if(TMR1IFG){
        TMR1IFG = 0;
        tmr_TMR1Reset();
        if (TMR1IntType == INT_DELAY){
            
            rtc_ISR();
        }
        if (TMR1IntType == INT_CANDLE){
            
            led_Toggle();
        }
    }
    
    
    if (CCP1_IF){   
        CCP1_IF = 0;
        //TMR1 = 0;
        //ccp_CCP1CompareMatch();
    }
    
    
    
    if (TMR0IFG){
        TMR0IFG = 0;
        //LED1LAT=0;
        //LED1LAT=1;
        tmr_TMR0IncRollovers();
        
        
    }
    
    /*
  if ( UCA0RXIFG )
  {
    QIn( UCA0RXBUF, getU0_RxBuf_t() );
    printf("PIR3 = %d \r\n",PIR3);
    LATAbits.LATA2 ^= 1;
    BAUD1CONbits.WUE = 1;
  }
  */
   /*
    if(PIR1bits.RCIF){
        TXREG = 'a';
        //BAUDCONbits.WUE=1; //doesn't work
        check = 1;
        rxChar = RCREG;
        //rxChar2 = RCREG; //doesn't work
        BAUDCONbits.WUE = 1; //making this ^= always makes the interrupt run twice
        //rxChar2 = RCREG; //doesnt work
        
    }
    */
    
    return;
}

