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

#define master

//#include <stdio.h>
//#include <stdlib.h>
#include <xc.h>
#include <pic16lf1455.h>
//#include <pic16f1455.h>

#pragma config FOSC=INTOSC, FCMEN=ON, WDTE=OFF, IESO=ON, LVP=ON 
#pragma config  PWRTE = OFF, BOREN = ON, STVREN = OFF, PLLEN = DISABLED

/*
 * 
 */

void configureInterrupt();
void configureUART();
configureUARTrXint();
volatile char check = 0;
volatile char rxChar = 0;



interrupt ISR(void){
    if(INTCONbits.IOCIF){

        IOCAFbits.IOCAF0 = 0; //YOU MUST CLEAR THE PIN SPECIFIC INTERRUPT FIRST 
        INTCONbits.IOCIF = 0;
        check = 1;
        
    }
    
    if(PIR1bits.RCIF){
        check = 1;
        rxChar = RCREG;
    }
    
    
    return;
}


int main(int argc, char** argv) {
    
    configUART();

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
    TRISAbits.TRISA5 = 0;
    LATAbits.LATA5 = 0;
    while(1){
        if (check){
            check = 0;
            //retrieve RX buffer contents
            
            if (rxChar =='a'){
                rxChar = 0;
                LATAbits.LATA5 ^= 1;
            }
            //SLEEP();
        }
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
}

configureUARTrXint(){
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}