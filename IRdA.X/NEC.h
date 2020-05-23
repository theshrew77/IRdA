/* 
 * File:   NEC.h
 * Author: 10158431
 *
 * Created on May 3, 2020, 4:55 PM
 */

#ifndef NEC_H
#define	NEC_H
/*
//Fosc = 16Mhz settings
#define NEC_START_LOW   10800
#define NEC_START_HIGH  16200
#define NEC_0_LOW       1000
#define NEC_0_HIGH      1500
#define NEC_1_LOW       2000
#define NEC_1_HIGH      3000

*/
/*
//Fosc = 32768 settings timer 1
#define NEC_START_LOW   353
#define NEC_START_HIGH  530
#define NEC_0_LOW       32
#define NEC_0_HIGH      48
#define NEC_1_LOW       64
#define NEC_1_HIGH      97
*/
/*
//Fosc = 32768 settings timer 0
#define NEC_START_LOW   44
#define NEC_START_HIGH  66
#define NEC_0_LOW       4
#define NEC_0_HIGH      6
#define NEC_1_LOW       8
#define NEC_1_HIGH      12
*/

//Fosc = 1MHz timer 0
#define NEC_START_LOW   2700
#define NEC_START_HIGH  4050
#define NEC_0_LOW       250
#define NEC_0_HIGH      375
#define NEC_1_LOW       500
#define NEC_1_HIGH      750
#define NEC_TIMEOUT     0

/*
//Fosc = 4MHz external oscillator timer 0
#define NEC_START_LOW   8160
#define NEC_START_HIGH  12240
#define NEC_0_LOW       1000
#define NEC_0_HIGH      1500
#define NEC_1_LOW       2000
#define NEC_1_HIGH      3000
#define NEC_TIMEOUT     0
*/
#define NEC_ADDRESS     0

typedef enum {
    LEDON   =   0xFF,
    LEDOFF     =   0xBF,
    TIMER2H =   0xDF,    
    TIMER4H =   0x9F, 
    TIMER6H =   0xEF, 
    TIMER8H =   0xAF, 
    DIM =       0xF7, 
    BRIGHT =    0xB7, 
} NEC_commands_t;

uint8_t nec_ProcessPacket(void);
void nec_ExecuteCommand(uint8_t NECcommand);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* NEC_H */

