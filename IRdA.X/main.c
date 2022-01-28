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
    led_Off();
    configureIOCInt();
    tmr_TMR0Init();
    tmr_TMR0reset();
    tmr_TMR1Init();
 
    while(1){
        SLEEP();       
        if(IR_received){                        //if woken up by an interrupt, check if it was from an IOC interrupt. IR_received = 1 for that interrupt type
            while(!accquisitionComplete());     //if interrupt was IOC wait for acquissition to be complete. This is set in tmr_TMR0.c
            G_IE = 0;                           //disable interrupts so the command can be processed properly
            //process to NEC
            //check for NEC start condition
            NECcommand = nec_ProcessPacket();   //convert the timestamps corresponding to IOC into a numerical value
            nec_ExecuteCommand(NECcommand);     //execute code associated with specific NEC command      
            tmr_TMR0reset();                    //reset the arrray of timestamps, sample number and acquistion status to 0
            IR_received = 0;                    
            G_IE = 1;                           //re-enable global interrupts
        }
        
      
    }

    return (EXIT_SUCCESS);
}





