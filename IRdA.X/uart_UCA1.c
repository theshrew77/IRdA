/*
 * uart_UCA1.c
 *
 *  Created on: Feb 8, 2019
 *      Author: KentDieball
 */

/* Includes ------------------------------------------------------------------*/

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"
//#include "HWInit.h"
//#include "RTC.h"
//#include "Scheduler.h"
#include "uart_UCA1.h"
#include "Que.h"

/* External variables --------------------------------------------------------*/
t_Q  U1_RxBuf_t;

/* External function prototypes ----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

t_Q* getU1_RxBuf_t(void){
    return(&U1_RxBuf_t);
}
void Uart_UCA1Init(void)
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

void Uart_UCA1deInit(void)
{
    
}

int8_t  Uart_UCA1_kbhit(void)
{
  return(QChkQ(&U1_RxBuf_t));
}

int8_t  Uart_UCA1_getc( int8_t *Out )
{
  return(QOut(Out, &U1_RxBuf_t) );
}

int8_t  Uart_UCA1_putc( int8_t c )
{
  while(!(UC1IFG & UCA1TXIFG));
  UCA1TXBUF = c;
  return(c);
}

//=============================================================================
