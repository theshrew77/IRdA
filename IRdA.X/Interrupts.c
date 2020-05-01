#include <xc.h>
#include "main.h"
#include "uart_UCA0.h"
#include "uart_UCA1.h"
#include <stdint.h>



__interrupt() void ISR(void){
    /*
    if(INTCONbits.IOCIF){

        IOCAFbits.IOCAF0 = 0; //YOU MUST CLEAR THE PIN SPECIFIC INTERRUPT FIRST 
        INTCONbits.IOCIF = 0;
        //check = 1;
        
    }
    */
  if ( UCA0RXIFG )
  {
    QIn( UCA0RXBUF, getU0_RxBuf_t() );
    LATAbits.LATA2 ^= 1;
  }
  
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

