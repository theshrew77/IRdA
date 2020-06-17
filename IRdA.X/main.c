/* 
 * File:   main.c
 * Author: jense
 *
 * Created on April 14, 2020, 7:54 PM
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "Debug.h"
#include "main.h"
#include "Interrupts.h"
#include "tmr_TMR0.h"
#include "NEC.h"
#include "LED.h"
#include "Oscillator.h"
#include "PowerManagement.h"
#include "tmr_TMR1.h"
#include "RTC.h"



volatile uint8_t IR_received = 0;




int main(int argc, char** argv) {
    
    
    uint8_t NECcommand = 0;
    
    CPUDOZEbits.IDLEN = 0;
    osc_Config1MHz();
    pwrmgmt_DisablePeripherals();
    
    rtc_Reset();

    led_ConfigureLED();
   
    led_Bright();
    configureIOCInt();
    
    tmr_TMR0Init();
    tmr_TMR0reset();
    
    tmr_TMR1Init();
 
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
            G_IE = 1;
        }
        
      
    }

    return (EXIT_SUCCESS);
}





