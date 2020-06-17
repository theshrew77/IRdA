/* 
 * File:   NEC.h
 * Author: 10158431
 *
 * Created on May 3, 2020, 4:55 PM
 */

#ifndef NEC_H
#define	NEC_H


//Fosc = 1MHz timer 0
#define NEC_START_LOW   2700
#define NEC_START_HIGH  4050
#define NEC_0_LOW       250
#define NEC_0_HIGH      375
#define NEC_1_LOW       500
#define NEC_1_HIGH      750
#define NEC_TIMEOUT     0


#define NEC_ADDRESS     0 
//#define OLDREMOTE
//#define GRANDINROAD
#define SCOTTLIVING
//#define LGTV

#ifdef OLDREMOTE
typedef enum {
    LEDON   =   0xFF,
    LEDOFF  =   0xBF,
    TIMER2H =   0xDF,    
    TIMER4H =   0x9F, 
    TIMER6H =   0xEF, 
    TIMER8H =   0xAF, 
    DIM =       0xF7, 
    BRIGHT =    0xB7, 
    CANDLE =    0xCF,
    LIGHT =     0x8F
} NEC_commands_t;
#endif

#ifdef GRANDINROAD
typedef enum {
    LEDON   =   0x7F,
    LEDOFF  =   0xFF,
    TIMER2H =   0xCF,    
    TIMER4H =   0x6F, 
    TIMER6H =   0xAF, 
    TIMER8H =   0x57, 
    DIM =       0x8F, 
    BRIGHT =    0xD7, 
    CANDLE =    0x4F,
    LIGHT =     0x97
} NEC_commands_t;
#endif

#ifdef SCOTTLIVING
typedef enum {
    LEDON   =   0xFF,
    LEDOFF  =   0x7F,
    TIMER2H =   0xBF,    
    TIMER4H =   0x3F, 
    TIMER6H =   0xDF, 
    TIMER8H =   0x5F, 
    DIM =       0x6F, 
    BRIGHT =    0x1F, 
    CANDLE =    0x4F,
    LIGHT =     0x97
} NEC_commands_t;
#endif

#ifdef LGTV
typedef enum {
    LEDON   =   0xB1,
    LEDOFF  =   0x71,
    TIMER2H =   0xBF,    
    TIMER4H =   0x3F, 
    TIMER6H =   0xDF, 
    TIMER8H =   0x5F, 
    DIM =       0x39, 
    BRIGHT =    0x79, 
    CANDLE =    0x4F,
    LIGHT =     0x97
} NEC_commands_t;
#endif
uint8_t nec_ProcessPacket(void);
void nec_ExecuteCommand(uint8_t NECcommand);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* NEC_H */

