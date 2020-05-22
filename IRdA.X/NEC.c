#include <xc.h>
#include <stdint.h>
#include "NEC.h"
#include "tmr_TMR0.h"
#include "uart_UCA0.h"
#include "LED.h"
#include "main.h"


uint8_t nec_ProcessPacket(void){
    uint16_t delta;
    uint8_t NECpacket [32] = {0};
    uint8_t command = 0;
    
    delta = tmr_computeDelta(0);
    

    if (NEC_START_LOW < delta && delta < NEC_START_HIGH){
        

        for (int i = 1; i < 33; i++){
            delta = tmr_computeDelta(i);
            if (NEC_0_LOW < delta && delta < NEC_0_HIGH){
                NECpacket[i-1] = 0;
            }
            if (NEC_1_LOW < delta && delta < NEC_1_HIGH){
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
    LEDLAT = 0;
    switch (NECcommand)
    {
        case POWER:
            //Uart_UCA0_putc( 'a' );
            led_Blink(1);
            break;
        case OFF:
            //Uart_UCA0_putc( 'b' );
            led_Blink(2);
            break;
        case TIMER2H:
            //Uart_UCA0_putc( 'c' );
            break;
        case TIMER4H:
            //Uart_UCA0_putc( 'd' );
            break;
        case TIMER6H:
            //Uart_UCA0_putc( 'e' );
            break;
        case TIMER8H:
            //Uart_UCA0_putc( 'f' );
            break;
        case DIM:
            //Uart_UCA0_putc( 'g' );
            break;
        case BRIGHT:
            //Uart_UCA0_putc( 'h' );
            break;
    }
}
