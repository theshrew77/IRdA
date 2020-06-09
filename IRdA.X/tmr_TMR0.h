/* 
 * File:   tmr_TMR0.h
 * Author: 10158431
 *
 * Created on May 10, 2020, 11:00 AM
 */

#ifndef TMR_TMR0_H
#define	TMR_TMR0_H

#define	TMR_TMR0_H
#define TMR0IFG     PIR0bits.TMR0IF
#define TMR0_IE     PIE0bits.TMR0IE
#define TMR0MAX     0xFF
#define TMR0PRE     T0CON1bits.T0CKPS
#define TMR016BEN   T0CON0bits.T016BIT
#define TMR0CS      T0CON1bits.T0CS
#define TMR0_ON     T0CON0bits.T0EN
//TMR0_PLX are pre-load bytes to make the timer roll over faster after acquiring
//an NEC signal. According to spec, the NEC packet should be 13.5+16*(1.25+2.5) = 73.5 ms
//preloading with 0xB815 means the timer will rollover after (0xFFFF - 0xB815)*4e-6 = 73.6 ms @ Fosc = 1MHZ and tmr0 clock source = Fosc/4
#define TMR0_PLH    0xB8
#define TMR0_PLL    0x15


void tmr_TMR0Init(void);
uint16_t tmr_computeDelta(uint8_t i);
uint8_t accquisitionComplete(void);
void tmr_TMR0mark(void);
void tmr_TMR0reset(void);
void tmr_TMR0IncRollovers(void);
void tmr_TMR0Dis(void);
void tmr_TMR0_PrintCountArray(void);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TMR_TMR0_H */

