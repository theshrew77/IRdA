/* 
 * File:   Interrupts.h
 * Author: 10158431
 *
 * Created on May 2, 2020, 10:58 PM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H
#define P_IE        INTCONbits.PEIE
#define G_IE        INTCONbits.GIE
#define IOC_IE      PIE0bits.IOCIE
#define IOC_IF      PIR0bits.IOCIF
#define IOCA_N      IOCANbits.IOCAN1
#define IOCA_TRIS   TRISAbits.TRISA1
#define IOCA_ANSEL  ANSELAbits.ANSA1
#define IOCA_F      IOCAFbits.IOCAF1


/*
 This enum is used to make the same timer execute interrupts on 2 
 * different timescales. Delay is for hour long timers. Candle is for
 * strobing the LED. This feature is only applicable if a remote with a
 * candle button is included.
 */
typedef enum{
    INT_DELAY = 0,
    INT_CANDLE = 1        
} TMR1InterruptTypes_t;

void configureIOCInt(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPTS_H */

