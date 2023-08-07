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
#define TMR1_1s     0x8003 //For 32.768KHz crystal this should be 0x8000 to
                           //give 1 second tick. Testing 01-00-010 PCBA
                           //suggested actual f was 32.763KHz i.e. 5Hz slower
                           //so pre load is increased by 5. This must be 
                           //determined for each PCBA
#define TMR1_candle 0xF999
#define TMR1PRE     T1CONbits.T1CKPS
#define TMR1CS      T1CONbits.TMR1CS
#define TMR1_ON     T1CONbits.TMR1ON
#define TMR1_IE     PIE1bits.TMR1IE
#define TMR1XTALEN  T1CONbits.T1SOSC


void tmr_TMR1setPreload(uint16_t preload);
void tmr_TMR1Init(void);
void tmr_TMR1SOSCpowerLevel(char level);
void tmr_TMR1En(void);
void tmr_TMR1Dis(void);
void tmr_TMR1Reset(void);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TMR_TMR1_H */

