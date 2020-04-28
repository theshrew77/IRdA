/* 
 * File:   main.c
 * Author: jense
 *
 * Created on April 14, 2020, 7:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 16000000
#define LEDonPin  5
#define LEDoffPin 4
#define LEDlat LATC

#define slave

//#include <stdio.h>
//#include <stdlib.h>
#include <xc.h>

#pragma config FOSC=INTOSC, FCMEN=ON, WDTE=OFF, IESO=ON, LVP=ON 
#pragma config  PWRTE = OFF, BOREN = ON, PLLEN = ON, STVREN = OFF, CLKOUTEN=ON
//test
/*
 * 
 */

void configureInterrupt();
void configureUART();
configureUARTrXint();
volatile char check = 0;
volatile char rxChar = 0;
volatile char rxChar2 = 0;



interrupt ISR(void){
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


int main(int argc, char** argv) {
    //INTCONbits.PEIE = 0;
    //INTCONbits.GIE = 0;
    OSCCON |= 0b00111110; //set oscilator frequency to 16MHz
//    __delay_ms(10);
    configUART();
    //TRISAbits.TRISA4 = 0;
#ifdef master
    configureInterrupt();
    while(1){
        if(check){
            check = 0;
            TXREG = 'a';
            //SLEEP();
        }
    }
#endif master
    
#ifdef slave
    configureUARTrXint();
    TRISCbits.TRISC3 = 0;
    LATCbits.LATC3 = 1;
    

    
    check = 0;
    while(1){
 
        if (check){
            check = 0;
            __delay_ms(10); //with this delay the interrupt still fires 2x but the LED behaves as expected
            
            //TXREG = 'b';
            //retrieve RX buffer contents
            
            //if (rxChar =='a'){
                rxChar = 0;
                LATCbits.LATC3 ^= 1; //This has nothing to do with it
                //BAUDCONbits.WUE = 1; //doesn't work
            //}
            //check = 0;

        }
        //BAUDCONbits.WUE = 1; //putting this here calls the interrupt twice but LED behavior is normal
        //SLEEP();
        NOP();
    }
#endif    
    return (EXIT_SUCCESS);
}


void configureInterrupt(){
    //enable interrupt on change
    INTCON = 0b10001000; //enable global interrupts and interrupt on change
    IOCANbits.IOCAN0 = 1; //enable negative edge detection on RA0
    //UCONbits.USBEN = 0;
    //configure RA0 as intterupt on change
    //RA0 is always input so don't need to set TRIS
    //RA0 has no ANSEL requirement
}

configUART(){
    //Enable TX
    TXSTAbits.TXEN = 1; //enable transmitter circuitry
    TXSTAbits.SYNC = 0; // configure for asynchronous operation
    RCSTAbits.SPEN = 1; //enable EUSART and configure TX as output
    //TX/RC4 has no ANSEL bit
    
    //enable RX
    RCSTAbits.CREN = 1; //enable receiver circuitry
    
    
    //configure 9600 baud
    TXSTAbits.BRGH = 0;
    BAUDCONbits.BRG16 = 0;
    SPBRGL = 25;
    
    //BAUDCONbits.WUE = 1;
}

configureUARTrXint(){
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}