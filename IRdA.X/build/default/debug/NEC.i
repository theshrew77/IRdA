# 1 "NEC.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "NEC.c" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 2 3
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 127 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 142 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 158 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 188 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 229 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 139 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 139 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdint.h" 2 3
# 1 "NEC.c" 2

# 1 "./NEC.h" 1
# 20 "./NEC.h"
typedef enum {
    POWER = 0xFF,
    OFF = 0xBF,
    TIMER2H = 0xDF,
    TIMER4H = 0x9F,
    TIMER6H = 0xEF,
    TIMER8H = 0xAF,
    DIM = 0xF7,
    BRIGHT = 0xB7,
} NEC_commands_t;

uint8_t nec_ProcessPacket(void);
void nec_ExecuteCommand(uint8_t NECcommand);
# 2 "NEC.c" 2

# 1 "./tmr_TMR1.h" 1
# 20 "./tmr_TMR1.h"
void tmr_TMR1Init(void);
void tmr_TMR1ClrRollovers(void);
uint16_t *tmr_TMR1GetRollovers(void);
void tmr_TMR1IncRollovers(void);
void tmr_TMR1En(void);
void tmr_TMR1Dis(void);
void tmr_TMR1Toggle(void);
uint32_t tmr_TMR1GetCount(void);
void tmr_TMR1reset(void);
void tmr_TMR1mark(void);
uint8_t accquisitionComplete(void);
uint16_t *getTMR1countArray(void);
uint16_t *getTMR1rolloverArray(void);
uint16_t tmr_computeDelta(uint8_t i);
# 3 "NEC.c" 2

# 1 "./uart_UCA0.h" 1
# 11 "./uart_UCA0.h"
# 1 "./Que.h" 1
# 14 "./Que.h"
typedef struct {
  int8_t Data[2];
  int8_t In;
  int8_t Out;
} t_Q;


int8_t QInit( t_Q *pQ );
int8_t QIn( int8_t Src, t_Q *pQ );
int8_t QOut( int8_t *Dest, t_Q *pQ );
int8_t QChkQ( t_Q *pQ );
# 11 "./uart_UCA0.h" 2








void Uart_UCA0Init(void);
void Uart_UCA0deInit(void);
int8_t Uart_UCA0_Flush(void);
int8_t Uart_UCA0_kbhit(void);
int8_t Uart_UCA0_getc( int8_t *Out );
int8_t Uart_UCA0_putc( int8_t c );
t_Q *getU0_RxBuf_t(void);
void Uart_UCA0_RxIntEn(void);
# 4 "NEC.c" 2



uint8_t nec_ProcessPacket(void){
    uint16_t delta;
    uint8_t NECpacket [32];
    uint8_t command = 0;

    delta = tmr_computeDelta(0);

    if (10800 < delta && delta < 16200){

        for (int i = 1; i < 33; i++){
            delta = tmr_computeDelta(i);
            if (1000 < delta && delta < 1500){
                NECpacket[i-1] = 0;
            }
            if (2000 < delta && delta < 3000){
                NECpacket[i-1] = 1;
            }
        }

        command += NECpacket[31];
        command += NECpacket[30]*2;
        command += NECpacket[29]*4;
        command += NECpacket[28]*8;
        command += NECpacket[27]*16;
        command += NECpacket[26]*32;
        command += NECpacket[25]*64;
        command += NECpacket[24]*128;

    }
    return(command);
}

void nec_ExecuteCommand(uint8_t NECcommand){

    switch (NECcommand)
    {
        case POWER:
            Uart_UCA0_putc( 'a' );
            break;
        case OFF:
            Uart_UCA0_putc( 'b' );
            break;
        case TIMER2H:
            Uart_UCA0_putc( 'c' );
            break;
        case TIMER4H:
            Uart_UCA0_putc( 'd' );
            break;
        case TIMER6H:
            Uart_UCA0_putc( 'e' );
            break;
        case TIMER8H:
            Uart_UCA0_putc( 'f' );
            break;
        case DIM:
            Uart_UCA0_putc( 'g' );
            break;
        case BRIGHT:
            Uart_UCA0_putc( 'h' );
            break;
    }
}
