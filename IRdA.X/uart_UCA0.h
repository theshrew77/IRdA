/* 
 * File:   uart_UCA0.h
 * Author: 10158431
 *
 * Created on April 29, 2020, 8:28 PM
 */

#ifndef UART_UCA0_H
#define	UART_UCA0_H
#include <stdint.h>
#include "Que.h"

#define UCA0TXBUF TX1REG
#define UCA0RXBUF RC1REG
#define IFG2 PIR3
#define UCA0TXIFG   PIR1bits.TXIF
#define UCA0RXIFG   PIR1bits.RCIF
#define REC_IE      PIE1bits.RCIE

void    Uart_UCA0Init(void);
void    Uart_UCA0deInit(void);
int8_t  Uart_UCA0_Flush(void);
int8_t  Uart_UCA0_kbhit(void);
int8_t  Uart_UCA0_getc( int8_t *Out );
int8_t  Uart_UCA0_putc( int8_t c );
t_Q     *getU0_RxBuf_t(void);
void    Uart_UCA0_RxIntEn(void);
void Uart_UCA0_puts(char*string);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* UART_UCA0_H */

