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
#include "uart_UCA0.h"






//#include <stdio.h>
//#include <stdlib.h>


// PIC16LF15313 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = ECH    // External Oscillator mode selection bits (EC above 8MHz; PFM set to high power)
#pragma config RSTOSC = HFINT1  // Power-up default value for COSC bits (HFINTOSC (1MHz))
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit (CLKOUT function is enabled; FOSC/4 clock appears at OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (FSCM timer enabled)

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR pin is Master Clear function)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = ON       // Brown-out reset enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit can be cleared and set only once in software)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep; SWDTEN ignored)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4
#pragma config BBSIZE = BB512   // Boot Block Size Selection bits (512 words boot block size)
#pragma config BBEN = OFF       // Boot Block Enable bit (Boot Block disabled)
#pragma config SAFEN = OFF      // SAF Enable bit (SAF disabled)
#pragma config WRTAPP = OFF     // Application Block Write Protection bit (Application Block not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block not write protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration Register not write protected)
#pragma config WRTSAF = OFF     // Storage Area Flash Write Protection bit (SAF not write protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.)

// CONFIG5
#pragma config CP = OFF         // UserNVM Program memory code protection bit (UserNVM code protection disabled)
//test
/*
 * 
 */

void configureInterrupt();


volatile char check = 0;
volatile char rxChar = 0;
volatile char rxChar2 = 0;

/*
__interrupt() void ISR(void){
    if(INTCONbits.IOCIF){

        IOCAFbits.IOCAF0 = 0; //YOU MUST CLEAR THE PIN SPECIFIC INTERRUPT FIRST 
        INTCONbits.IOCIF = 0;
        //check = 1;
        
    }
    
    if(PIR1bits.RCIF){
        TXREG = 'a';
        //BAUDCONbits.WUE=1; //doesn't work
        check = 1;
        rxChar = RCREG;
        //rxChar2 = RCREG; //doesn't work
        BAUDCONbits.WUE = 1; //making this ^= always makes the interrupt run twice
        //rxChar2 = RCREG; //doesnt work
        
    }
    
    
    return;
}
*/

int main(int argc, char** argv) {

    
    //set oscilator frequency to 16MHz
    OSCFRQ = 0b0000101;  
    OSCCON1 = 0b01100000;

    Uart_UCA0Init();
    configureInterrupt();

//    __delay_ms(10);
//    configUART();
    
    //TRISAbits.TRISA4 = 0;

    

    Uart_UCA0_RxIntEn();
    TRISAbits.TRISA2 = 0;
    LATAbits.LATA2 = 0; 
    __delay_ms(500);


    printf("Entering while(1) \n\r");
    //printf("Pizza Timex%d! \n\r",5);
    while(1){

        //TX1REG = 'a';
        //Uart_UCA0_putc( 'a' );
        
        //LATAbits.LATA2 ^= 1;
        //__delay_ms(500);

        //TX1REG = 'a';
        //LATAbits.LATA2 ^= 1;
       // __delay_ms(100);

    }
   
    

    
    check = 0;
    while(1){
 
        if (check){
            check = 0;
            __delay_ms(10); //with this delay the interrupt still fires 2x but the LED behaves as expected
            
            //TXREG = 'b';
            //retrieve RX buffer contents
            
            //if (rxChar =='a'){
                rxChar = 0;
                //LATCbits.LATC3 ^= 1; //This has nothing to do with it
                //BAUDCONbits.WUE = 1; //doesn't work
            //}
            //check = 0;

        }
        //BAUDCONbits.WUE = 1; //putting this here calls the interrupt twice but LED behavior is normal
        //SLEEP();
        NOP();
    }
  
    return (EXIT_SUCCESS);
}


void configureInterrupt(){
    //enable interrupt on change
    PIE0bits.IOCIE = 1;
    //enable global interrupts
    INTCONbits.GIE = 1;
    
    //enable IOCA4 for negative edge detection
    IOCANbits.IOCAN4 = 1;
    TRISAbits.TRISA4 = 1;
    ANSELAbits.ANSA4 = 0;
    //INTCON = 0b10001000; //enable global interrupts and interrupt on change
    //IOCANbits.IOCAN0 = 1; //enable negative edge detection on RA0
    //UCONbits.USBEN = 0;
    //configure RA0 as intterupt on change
    //RA0 is always input so don't need to set TRIS
    //RA0 has no ANSEL requirement
}



