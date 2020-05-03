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
#define IOCA_N      IOCANbits.IOCAN4
#define IOCA_TRIS   TRISAbits.TRISA4
#define IOCA_ANSEL  ANSELAbits.ANSA4
#define IOC_IF      PIR0bits.IOCIF
#define IOCA_F      IOCAFbits.IOCAF4

void configureIOCInt(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPTS_H */

