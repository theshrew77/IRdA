/* 
 * File:   Oscillator.h
 * Author: 10158431
 *
 * Created on May 5, 2020, 10:05 PM
 */

#ifndef OSCILLATOR_H
#define	OSCILLATOR_H

#define XTAL_READY  OSCSTAT1bits.EXTOR
#define OSC_READY   OSCCON3bits.ORDY

#ifdef	__cplusplus
extern "C" {
#endif
void _osc_Config32768Hz(void);
void osc_Config16MHz(void);
void osc_Config1MHz(void);


#ifdef	__cplusplus
}
#endif

#endif	/* OSCILLATOR_H */

