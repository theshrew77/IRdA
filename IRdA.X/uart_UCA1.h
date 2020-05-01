/* 
 * File:   uart_UCA1.h
 * Author: 10158431
 *
 * Created on April 29, 2020, 8:32 PM
 */

#ifndef UART_UCA1_H
#define	UART_UCA1_H
#include "Que.h"

#define UCA1TXBUF TXREG
#define UCA1RXBUF RCREG
#define UC1IFG PIR3
#define UCA1TXIFG PIR3bits.TX1IF
#define UCA1RXIFG PIR3bits.RC1IF

void    Uart_UCA1Init(void);
void    Uart_UCA1deInit(void);
int8_t  Uart_UCA1_Flush(void);
int8_t  Uart_UCA1_kbhit(void);
int8_t  Uart_UCA1_getc( int8_t *Out );
int8_t  Uart_UCA1_putc( int8_t c );
t_Q     *getU1_RxBuf_t(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* UART_UCA1_H */

