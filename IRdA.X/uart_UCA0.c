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
    RA0PPS = 0x0F;
    TX1STAbits.TXEN = 1;
    TX1STAbits.SYNC = 0;
    RC1STAbits.SPEN = 1;
    //clear RA0/TX ANSEL bit
    ANSELAbits.ANSA0 = 0;
    
    //enable RX
    RC1STAbits.CREN = 1; //enable receiver circuitry
    
    
    //configure 9600 baud @ 16MHZ Fosc
    TX1STAbits.BRGH = 0;
    BAUD1CONbits.BRG16 = 0;
    SPBRGL = 25;
    
    //BAUDCONbits.WUE = 1;   
    
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

/**
  * @brief  Receive interrupt for the uart.
  *         The received byte is placed in the input queue.
  * @param  none
  * @retval none
  */

