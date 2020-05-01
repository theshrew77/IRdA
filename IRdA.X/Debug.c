
/**
  ******************************************************************************
  ******************************************************************************
  * @file     : Debug.c
  * @brief    : Print function for debugging.
  * @author   : Kent Dieball
  * @version  : 01.01
  * @date     : 20190911
  ******************************************************************************
  * Copyright 2019 Flowserve Corporation
  *
  * This software is proprietary and trade secret to Flowserve Corporation.
  * Any use or disclosure without written permission of Flowserve is strictly
  * forbidden.
  *
  * Flowserve Corporation
  * XXXX
  * XXXX
  *
  ******************************************************************************
  * DESCRIPTION :
  *   Functions to perform queuing functions.
  *
  ******************************************************************************
  * CHANGES:
  * VERSION   DATE    AUTHOR    DETAIL
  * 01.00   20190430  Dieball   First version
  * 01.01   20190911  Dieball   Removed the RS485 specific instructions
  *
  ******************************************************************************
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
#include "Debug.h"
#include "uart_UCA0.h"
#include "Retarget.h"
//#include "TmrDelay.h"

/* External variables --------------------------------------------------------*/
/* External function prototypes ----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint16_t DebugEna = TRUE;


/* Private function prototypes -----------------------------------------------*/

void debug_init(void)
{
  Uart_UCA0Init();        //! initialize and start uart0
  DebugEna = TRUE;
  //TmrDelay(500);
  __delay_ms(500);
}
void debug_deinit(void)
{
  Uart_UCA0deInit();      //! de-initialize uart0
  DebugEna = FALSE;
}

/*----------------------------------------------------------------------------
  print to debug port
 *----------------------------------------------------------------------------*/
void debug_out(const char *fmt, ...)
{
  va_list arg_ptr;
  if (TRUE == DebugEna)
  {
    va_start (arg_ptr, fmt); /* format string */
    vfprintf( stdout, fmt, arg_ptr );
    va_end (arg_ptr);
  }
  else
  {
    _nop();
  }
}
char  *debug_in( char *buf, uint16_t Len, uint32_t tmo )
{
  if (TRUE == DebugEna)
  {
    _fflush(stdin);               // flush the rx buffer
    memset(buf,0,Len);
    _fgets(buf, Len, stdin );     // get the string
    //_fgets_tmo(buf, Len, stdin, tmo ); // get the string
    return(buf);
  }
  else
  {
    return(NULL);
  }
}

int16_t debug_kbhit(void)
{
  int16_t rval;

  if (TRUE == DebugEna)
  {
    rval = _fkbhit(stdin);
  }
  else
  {
    rval = -1;
  }
  return(rval);
}

uint16_t debug_enable(void)
{
  DebugEna = TRUE;
  return(DebugEna);
}

uint16_t debug_disable(void)
{
  DebugEna = FALSE;
  return(DebugEna);
}

uint16_t debug_getstatus(void)
{
  return(DebugEna);
}

void debug_flush(void)
{
  Uart_UCA0_Flush();
}
// == END OF FILE ==
