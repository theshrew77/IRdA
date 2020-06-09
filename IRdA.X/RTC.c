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
    
    if (++tRTC.Seconds == 60){
        if (++tRTC.Minutes == hourDelay){
                tmr_TMR1Dis();
                led_Off();             
        }
    }
   
    /*
    if (++tRTC.Seconds == 60){
        if (++tRTC.Minutes == 60){
            if(++tRTC.Hours == hourDelay){
                tmr_TMR1Dis();
                LEDLAT = 1;             
            } 
        }
    }
    */
    
 
}
