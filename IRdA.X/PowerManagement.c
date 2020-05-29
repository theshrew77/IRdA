#include <xc.h>


#include "PowerManagement.h"

    void pwrmgmt_DisablePeripherals(void){
        PMD0bits.FVRMD = 1;
        PMD0bits.NVMMD = 1;
        PMD0bits.CLKRMD = 1;
        //PMD0bits.SYSCMD = 1;
        
        PMD1bits.NCOMD = 1;
        PMD1bits.TMR2MD = 1;
        //PMD1bits.DDS1MD = 1;
        
        PMD2bits.DACMD = 1;
        PMD2bits.ADCMD = 1;
        PMD2bits.CMP1MD = 1;
        //PMD2bits.ZCDMD = 1;
        
        PMD3bits.CWG1MD = 1;
        PMD3bits.CCP2MD = 1;
        //PMD3bits.PWM3MD = 1;
        //PMD3bits.PWM4MD = 1;
        PMD3bits.PWM5MD = 1;
        PMD3bits.PWM6MD = 1;
        
        PMD4bits.UART1MD = 1;
        //PMD4bits.CWG1MD = 1;
        PMD4bits.MSSP1MD = 1;
        
        PMD5bits.CLC1MD = 1;
        PMD5bits.CLC2MD = 1;
        PMD5bits.DSMMD = 1;
        //PMD5bits.CLC3MD = 1;
        //PMD5bits.CLC4MD = 1;
        
    }
    void pwrmgmt_ConfigUnusedPins(void){
        TRISAbits.TRISA0 = 1;
        ANSELAbits.ANSA0 = 1;
    }
