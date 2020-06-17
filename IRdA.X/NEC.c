#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "NEC.h"
#include "tmr_TMR0.h"
#include "uart_UCA0.h"
#include "LED.h"
#include "main.h"
#include "RTC.h"
#include "tmr_TMR1.h"
#include "DAC.h"
#include "Interrupts.h"

uint8_t TMR1IntType;
char str[6];
char CRLF[4] = "\r\n";

uint8_t nec_ProcessPacket(void){
    uint16_t delta;
    uint8_t NECpacket [32] = {0};
    uint8_t command = 0;
    
    delta = tmr_computeDelta(0);

    if (NEC_START_LOW < delta && delta < NEC_START_HIGH){
        
        
        for (uint8_t i = 1; i < 33; i++){
            delta = tmr_computeDelta(i);
            if (NEC_0_LOW < delta && delta < NEC_0_HIGH){
                NECpacket[i-1] = 0;
            }
            if (NEC_1_LOW < delta && delta < NEC_1_HIGH){
                NECpacket[i-1] = 1;
            }
        }
        
        command += NECpacket[31];
        command += NECpacket[30]*2U;
        command += NECpacket[29]*4U;
        command += NECpacket[28]*8U;
        command += NECpacket[27]*16U;
        command += NECpacket[26]*32U;
        command += NECpacket[25]*64U;
        command += NECpacket[24]*128U;
        
    }
#ifdef DEBUGGING
    itoa(str,command,16);
    Uart_UCA0_puts(str);
    Uart_UCA0_puts(CRLF);
#endif
   

    
    return(command);
}

void nec_ExecuteCommand(uint8_t NECcommand){
    switch (NECcommand)
    {
        case LEDON:
            //Uart_UCA0_putc( 'a' );
            //LEDLAT = 0;
            tmr_TMR1Dis();
            led_Bright();  
            break;
        case LEDOFF:
            //Uart_UCA0_putc( 'b' );
            //LEDLAT = 1;
            led_Off();
            tmr_TMR1Dis();
            break;
        case TIMER2H:
            led_Bright();
            TMR1IntType = INT_DELAY;
            tmr_TMR1setPreload(TMR1_1s);
            tmr_TMR1SOSCpowerLevel('l');
            rtc_SetHourDelay(1);
            break;
        case TIMER4H:
            led_Bright();
            TMR1IntType = INT_DELAY;
            tmr_TMR1setPreload(TMR1_1s);
            tmr_TMR1SOSCpowerLevel('l');
            rtc_SetHourDelay(4);
            //Uart_UCA0_putc( 'd' );
            break;
        case TIMER6H:
            led_Bright();
            TMR1IntType = INT_DELAY;
            tmr_TMR1setPreload(TMR1_1s);
            tmr_TMR1SOSCpowerLevel('l');
            rtc_SetHourDelay(6);
            //Uart_UCA0_putc( 'e' );
            break;
        case TIMER8H:
            led_Bright();
            TMR1IntType = INT_DELAY;
            tmr_TMR1setPreload(TMR1_1s);
            tmr_TMR1SOSCpowerLevel('l');
            rtc_SetHourDelay(8);
            //Uart_UCA0_putc( 'f' );
            break;
        case DIM:
            //Uart_UCA0_putc( 'g' );
            //dac_DAClevelChange('d');
            led_Dim();
            break;
        case BRIGHT:
            led_Bright();
            //Uart_UCA0_putc( 'h' );
            //dac_DAClevelChange('u');
            break;
        case CANDLE:
            tmr_TMR1setPreload(TMR1_candle);
            TMR1IntType = INT_CANDLE;
            tmr_TMR1Reset();
            tmr_TMR1SOSCpowerLevel('h');
            tmr_TMR1En();
            break;
        case LIGHT:
            //Uart_UCA0_putc( 'a' );
            //LEDLAT = 0;
            tmr_TMR1Dis();
            led_Bright();
            break;
            
    }
}
