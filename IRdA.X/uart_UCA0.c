#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <xc.h>

#include "main.h"
#include "uart_UCA0.h"
#include "Que.h"

/* External variables --------------------------------------------------------*/
static t_Q  U0_RxBuf_t;

t_Q *getU0_RxBuf_t(void){
    return(&U0_RxBuf_t);
}

void Uart_UCA0Init(void)
{
   //Enable TX
    RA0PPS = 0x0F;          //send UART TX to RA0
    TX1STAbits.TXEN = 1;    //Enable Transmitter circuitry
    TX1STAbits.SYNC = 0;    //Disable synchronus mode
    RC1STAbits.SPEN = 1;    //Enable ESUART and set TX pin as output
    ANSELAbits.ANSA0 = 0;   //clear RA0/TX ANSEL bit
    
    
    //enable RX
    RX1DTPPS = 0x01;        //Retrieve UART RX from RA1
    TRISAbits.TRISA1 = 1;   //Set RX pin as input. Required for RX only; TX handled by setting SPEN
    ANSELAbits.ANSA1 = 0;   //clear RA1/RX ANSEL bit
    RC1STAbits.CREN = 1;    //enable receiver circuitry
    
    BAUD1CONbits.WUE = 1;   
    
    //configure 9600 baud
    TX1STAbits.BRGH = 0;
    BAUD1CONbits.BRG16 = 0;
    SPBRGL = 25;
    
}

void Uart_UCA0_RxIntEn(void){
    PIE3bits.RC1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    //BAUD1CONbits.WUE = 1;
}

void Uart_UCA0deInit(void)
{
    
}

int8_t  Uart_UCA0_Flush(void)
{
  QInit( &U0_RxBuf_t );
  return(TRUE);
}

/**
  * @brief  Check the input queue for a new entry.
  * @param  none
  * @retval void
  */
int8_t  Uart_UCA0_kbhit(void)
{
  return(QChkQ(&U0_RxBuf_t));
}

/**
  * @brief  Get the next entry from the input queue.
  * @param  *Out  - pointer to the destination byte.
  * @retval on success - TRUE
  *         on failure - FALSE, no new entries in the input queue.
  */
int8_t  Uart_UCA0_getc( int8_t *Out )
{
  return(QOut(Out, &U0_RxBuf_t) );
}

/**
  * @brief  Transmit a byte via the uart.
  * @param  c - byte to be output via the uart.
  * @retval c - the value transmitted by the uart.
  */
int8_t  Uart_UCA0_putc( int8_t c )
{
  while(!(UCA0TXIFG));
  UCA0TXBUF = c;
  return(c);
}


