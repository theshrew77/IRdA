#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "NEC.h"
#include "tmr_TMR0.h"
#include "tmr_TMR1.h"
#include "LED.h"
#include "main.h"
#include "RTC.h"
#include "Interrupts.h"

uint8_t TMR1IntType;


uint8_t nec_ProcessPacket(void){
    uint16_t delta;
    uint8_t NECpacket [32] = {0};
    uint8_t command = 0;
    uint8_t address = 0;
    
    delta = tmr_computeDelta(0);                            //compute the time between the first 2 falling edge IOC's. For NEC this should be 13.5 ms which is 2700 in tmr0 

    if (NEC_START_LOW < delta && delta < NEC_START_HIGH){   //checks if the value is correct +/-20%
        
        
        for (uint8_t i = 1; i < 33; i++){                   //NEC packets are 32 bits hence the 33
            delta = tmr_computeDelta(i);
            if (NEC_0_LOW < delta && delta < NEC_0_HIGH){   //checks if the value is correct +/-20%
                NECpacket[i-1] = 0;
            }
            if (NEC_1_LOW < delta && delta < NEC_1_HIGH){   //checks if the value is correct +/-20%
                NECpacket[i-1] = 1;
            }
        }
        
        //convert the last 8 bits to a command
        command += NECpacket[31];
        command += NECpacket[30]*2U;
        command += NECpacket[29]*4U;
        command += NECpacket[28]*8U;
        command += NECpacket[27]*16U;
        command += NECpacket[26]*32U;
        command += NECpacket[25]*64U;
        command += NECpacket[24]*128U;
        
        
        //convert the first 8 bits into an address
        address += NECpacket[7];
        address += NECpacket[6]*2U;
        address += NECpacket[5]*4U;
        address += NECpacket[4]*8U;
        address += NECpacket[3]*16U;
        address += NECpacket[2]*32U;
        address += NECpacket[1]*64U;
        address += NECpacket[0]*128U;
        
    }
    if (NEC_ADDRESS == address){
        return(command);
    }
    else
        return(0);
}

void nec_ExecuteCommand(uint8_t NECcommand){
    switch (NECcommand)
    {
        case LEDON:
            tmr_TMR1Dis();
            led_Bright();  
            tmr_TMR1Dis();
            break;
        case LEDOFF:
            led_Off();
            tmr_TMR1Dis();
            break;
        case TIMER2H:
            led_Bright();
            rtc_Reset();
            TMR1IntType = INT_DELAY;
            tmr_TMR1setPreload(TMR1_1s);
            tmr_TMR1SOSCpowerLevel('l');
            rtc_SetHourDelay(2);
            break;
        case TIMER4H:
            led_Bright();
            rtc_Reset();
            TMR1IntType = INT_DELAY;
            tmr_TMR1setPreload(TMR1_1s);
            tmr_TMR1SOSCpowerLevel('l');
            rtc_SetHourDelay(4);
            break;
        case TIMER6H:
            led_Bright();
            rtc_Reset();
            TMR1IntType = INT_DELAY;
            tmr_TMR1setPreload(TMR1_1s);
            tmr_TMR1SOSCpowerLevel('l');
            rtc_SetHourDelay(6);
            break;
        case TIMER8H:
            led_Bright();
            rtc_Reset();
            TMR1IntType = INT_DELAY;
            tmr_TMR1setPreload(TMR1_1s);
            tmr_TMR1SOSCpowerLevel('l');
            rtc_SetHourDelay(8);
            break;
        case DIM:
            led_Dim();
            break;
        case BRIGHT:
            led_Bright();
            break;
        case CANDLE:
            tmr_TMR1setPreload(TMR1_candle);
            TMR1IntType = INT_CANDLE;
            tmr_TMR1Reset();
            tmr_TMR1SOSCpowerLevel('h');
            tmr_TMR1En();
            break;
        case LIGHT:
            tmr_TMR1Dis();
            led_Bright();
            break;
            
    }
}
