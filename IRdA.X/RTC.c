#include<xc.h>
#include<stdint.h>
#include"RTC.h"
#include "tmr_TMR1.h"
#include "LED.h"

RTC_t tRTC;
uint8_t hourDelay = 0;

void rtc_SetHourDelay(uint8_t hours){
    hourDelay = hours;
    rtc_Reset();
    tmr_TMR1Reset();
    tmr_TMR1En();
    
}

void rtc_Reset(void){
    tRTC.Seconds = 0;
    tRTC.Minutes = 0;
    tRTC.Hours = 0;
}

void rtc_ISR(void){
  /*
    if (++tRTC.Seconds == 60){
        tRTC.Seconds = 0;
        if (++tRTC.Minutes == hourDelay){
            tRTC.Minutes = 0;
                tmr_TMR1Dis();
                led_Off();             
        }
    }
*/
    
    if (++tRTC.Seconds == 60){
        tRTC.Seconds = 0;
        if (++tRTC.Minutes == 60){
            tRTC.Minutes = 0;
            if(++tRTC.Hours == hourDelay){
                tRTC.Hours = 0;
                //tmr_TMR1Dis();
                //led_Off();  
                rtc_SetHourDelay(24 - hourDelay);
                led_Toggle();
            } 
        }
    }
    
  
 
}
