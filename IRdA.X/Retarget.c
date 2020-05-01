/**
  ******************************************************************************
  * @file   Retarget.c
  * @brief  targets the MCU serial port to the C standard formatted
  *         ports, stdin,stdout and stderr.
  *         stdin:  is targeted to uart0, connects to RS485 and BlueTooth
  *         stdout: is targeted to uart0, connects to RS485 and BlueTooth
  *         stderr: is targeted to uart0, connects to the Radio Module
  * @author Kent Dieball
  * @date   9-Apr-2019
  *
  *
  ******************************************************************************
  * @par
  * Copyright
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#include "main.h"
//#include "HWInit.h"
//#include "RTC.h"
//#include "Scheduler.h"
#include "uart_UCA0.h"
#include "uart_UCA1.h"
#include "Que.h"
#include "Retarget.h"

/* External variables --------------------------------------------------------*/
/* External function prototypes ----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#define FGETS_TMO   5   // 5 seconds
static int16_t SerialEcho = TRUE;
/* Private function prototypes -----------------------------------------------*/


void putch(char c){
    Uart_UCA0_putc( c );
}
