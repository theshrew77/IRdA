#include <xc.h>
#include <stdint.h>
#include "main.h"
#include "uart_UCA0.h"
#include "tmr_TMR1.h"
#include "Interrupts.h"
#include "LED.h"
//#include <stdio.h>

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

        IOCA_F = 0; //YOU MUST CLEAR THE PIN SPECIFIC INTERRUPT FIRST 
        IOC_IF = 0;
        //LATAbits.LATA2 ^= 1;
        //printf("TMR1 total count = %u\r\n",tmr_TMR1GetCount());
        //printf("TMR1 rollovers = %u\r\n",*tmr_TMR1GetRollovers());
        if (!TMR1_ON) TMR1_ON = 1;
        tmr_TMR1mark();
        //check = 1;
        
    }
    
    if(TMR1IFG){
        TMR1IFG = 0;
        //printf("TMR1 rolled over\r\n");
        tmr_TMR1IncRollovers();
        
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

