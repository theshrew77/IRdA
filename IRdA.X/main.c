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
#include "tmr_TMR1.h"
#include "NEC.h"









//test
/*
 * 
 */







int main(int argc, char** argv) {
    uint8_t NECcommand = 0;
    
    
    //set oscilator frequency to 16MHz
    OSCFRQ = 0b0000101;  
    OSCCON1 = 0b01100000;
    

    
    
    Uart_UCA0Init();
    configureIOCInt();
    tmr_TMR1Init();
    tmr_TMR1reset();

 
    TRISAbits.TRISA2 = 0;
    LATAbits.LATA2 = 0; 
    //__delay_ms(500);


    //printf("Entering while(1) \n\r");
    //printf("Pizza Timex%d! \n\r",5);
    
    while(1){
        SLEEP();
        NOP();
        while(!accquisitionComplete());
            //process to NEC
            //check for NEC start condition
            NECcommand = nec_ProcessPacket();
            nec_ExecuteCommand(NECcommand);          
            tmr_TMR1reset();
            __delay_ms(5);
        
    }

    return (EXIT_SUCCESS);
}





