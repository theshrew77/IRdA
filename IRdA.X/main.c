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
volatile char check = 0;

interrupt ISR(void){
    if(INTCONbits.IOCIF){

        IOCAFbits.IOCAF0 = 0; //YOU MUST CLEAR THE PIN SPECIFIC INTERRUPT FIRST 
        INTCONbits.IOCIF = 0;
        check = 1;
        
    }
    
    
    return;
}


int main(int argc, char** argv) {
    
    //configure UART
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;
    //RC4 has no ANSEL bit
    
    //This is a line to test what happens when switching branches
    
    TRISAbits.TRISA5 = 0;
    LATAbits.LATA5 = 0;
    configureInterrupt();
    while(1){
        if(check){
            LATAbits.LATA5 ^= 1;
            check = 0;
        }
        //__delay_ms(20);
        //LATAbits.LATA5 = 0;
        //__delay_ms(20);
    }
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