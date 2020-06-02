/* 
 * File:   main.c
 * Author: jense
 *
 * Created on April 14, 2020, 7:54 PM
 */
#include <xc.h>
//#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "Debug.h"
#include "main.h"
#include "uart_UCA0.h"
#include "Interrupts.h"
#include "tmr_TMR0.h"
#include "NEC.h"
#include "LED.h"
#include "Oscillator.h"
#include "PowerManagement.h"
#include "tmr_TMR1.h"
#include "ccp_CCP1.h"
#include "RTC.h"
#include "DAC.h"









//test
/*
 * 
 */



volatile uint8_t IR_received = 0;



int main(int argc, char** argv) {
    
    
    uint8_t NECcommand = 0;
    CPUDOZEbits.IDLEN = 0;
    osc_Config1MHz();
    pwrmgmt_ConfigUnusedPins();
    //pwrmgmt_DisablePeripherals();
    rtc_Reset();
    #ifdef _16F18313 
        VREGCONbits.VREGPM=1;
    #endif
    
    led_ConfigureLED();
    configureIOCInt();
    
    tmr_TMR0Init();
    tmr_TMR0reset();
    
    tmr_TMR1Init();
    
    dac_DACInit();
    dac_DACEn();
 
    //ccp_CCP1Init();
    
    //tmr_TMR1En();
    //ccp_CCP1En();
    
   
    while(1){
        SLEEP();       
        if(IR_received){
            while(!accquisitionComplete());
            G_IE = 0;
            //process to NEC
            //check for NEC start condition
            NECcommand = nec_ProcessPacket();
            nec_ExecuteCommand(NECcommand);          
            tmr_TMR0reset();
            IR_received = 0;
            __delay_ms(5);
            G_IE = 1;
        }
        
      
    }

    return (EXIT_SUCCESS);
}





