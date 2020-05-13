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









//test
/*
 * 
 */







int main(int argc, char** argv) {
    
    uint8_t NECcommand = 0;
    
    
    /*
    while(!OSCSTATbits.EXTOR); //wait for the external oscillator to be ready
    OSCENbits.EXTOEN = 1;       //explicitly enable external osciallator
    OSCCON1 = 0b01110000;       //set clock tree to accept external oscillator with 1:1 prescaler
    while(!OSCCON3bits.ORDY);   //wait for the oscillator to be ready
    */
    
    
    led_ConfigureLED();
  
    
    //Uart_UCA0Init();
    configureIOCInt();
    
    tmr_TMR0Init();
    tmr_TMR0reset();
    

    
    osc_Config1MHz();

    while(1){
        SLEEP();
        NOP();
        
        while(!accquisitionComplete());
        G_IE = 0;
        //process to NEC
        //check for NEC start condition
        NECcommand = nec_ProcessPacket();
        nec_ExecuteCommand(NECcommand);          
        tmr_TMR0reset();
        __delay_ms(5);
        G_IE = 1;
      
    }

    return (EXIT_SUCCESS);
}





