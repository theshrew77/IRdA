/* 
 * File:   tmr_TMR1.h
 * Author: 10158431
 *
 * Created on May 2, 2020, 7:08 PM
 */

#ifndef TMR_TMR1_H
#define	TMR_TMR1_H
#define TMR1IFG     PIR1bits.TMR1IF
#define TMR1MAX     0xFFFF
#define TMR1_1s     0x7FFF
#define TMR1PRE     T1CONbits.T1CKPS
//#define TMR116BEN   T1CONbits.RD16
#define TMR1CS      T1CONbits.TMR1CS
#define TMR1_ON     T1CONbits.TMR1ON
#define TMR1_IE     PIE1bits.TMR1IE
#define TMR1XTALEN  T1CONbits.T1SOSC



void tmr_TMR1Init(void);
void tmr_TMR1ClrRollovers(void);
uint16_t *tmr_TMR1GetRollovers(void);
void tmr_TMR1IncRollovers(void);
void tmr_TMR1En(void);
void tmr_TMR1Dis(void);
void tmr_TMR1Reset(void);
void tmr_TMR1Toggle(void);
uint32_t tmr_TMR1GetCount(void);
void tmr_TMR1reset(void);
void tmr_TMR1mark(void);
uint8_t accquisitionComplete(void);
uint16_t *getTMR1countArray(void);
uint16_t *getTMR1rolloverArray(void);
uint16_t tmr_computeDelta(uint8_t i);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TMR_TMR1_H */

