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
int16_t SetSerialEcho( int16_t val )
{
  if (TRUE == val)
  {
    SerialEcho = TRUE;
  }
  else
  {
    SerialEcho = FALSE;
  }
  return(SerialEcho);
}
/**
  * @brief  Directs the output of a byte to a specific output stream.
  * @param  _c - byte to be output
  * @param  _fp - file pointer to the output stream
  * @retval on success, returns _c
  *         on failure, returns EOF
  */
int fputc(int _c, register FILE *_fp)
{

  if ( stderr == _fp )                // stderr on uart 1
  {
    while(!(UC1IFG & UCA1TXIFG));
    UCA1TXBUF = (unsigned char) _c;
  }

  else if( stdout == _fp )              // all others to stdio on uart 0
  {
    while(!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = (unsigned char) _c;
  }
  else
  {
    _c = EOF;
  }
  return((unsigned char)_c);
}

/**
 *  @brief    writes a null terminated string to the output stream
 *  @param    _ptr - pointer to a null terminated sting
 *  @param    _fp  - pointer to the output stream
 *  @retval   on success, number of byte written
 *            on failure, EOF
 */
int fputs(const char *_ptr, register FILE *_fp)
{
  int i, len;

  len = strlen(_ptr);

  if ( stderr == _fp )                // stderr on uart 1
  {
    for(i=0 ; i<len ; i++)
    {
      Uart_UCA1_putc( _ptr[i] );
    }
  }
  else if (stdout == _fp )           // all others to stdio on uart 0
  {
    for(i=0 ; i<len ; i++)
    {
      Uart_UCA0_putc( _ptr[i] );
    }
  }
  else
  {
    len = EOF;
  }
  return( len );
}

/**
 *  @brief    Flushes the input queue
 *  @param    _fp  - pointer to the input stream
 *  @retval   on success, TRUE
 *            on failure, FALSE
 */
int   _fflush(FILE *_fp)
{
  int8_t c = EOF;

  if ( stderr == _fp )                // stderr on uart 1
  {
    c = Uart_UCA1_Flush();
  }
  else if ( stdin == _fp )            // all other from stdio on uart 0
  {
    c = Uart_UCA0_Flush();
  }
  else
  {
    c = FALSE;
  }
  return(c);
}

/**
 *  @brief    Reads the next byte from a input stream and returns it.
 *            _fgetc is a non-blocking function.
 *  @param    _fp  - pointer to the input stream
 *  @retval   on success, number of byte written
 *            on failure, EOF
 */
int   _fgetc(FILE *_fp)
{
  int8_t c = EOF;

  if ( stderr == _fp )                // stderr on uart 1
  {
    if ( TRUE == Uart_UCA1_kbhit() )
    {
      Uart_UCA1_getc( &c );           // get data from input from uart
    }
    else
    {
      c = EOF;
    }
  }
  else if ( stdin == _fp )            // all other from stdio on uart 0
  {
    if ( TRUE == Uart_UCA0_kbhit() )
    {
      Uart_UCA0_getc( &c );           // get data from input from uart
    }
    else
    {
      c = EOF;
    }
  }
  else
  {
    c = EOF;
  }
  return(c);
}

/**
 *  @brief    Reads the next byte from a input stream and returns it.
 *            _fgetchar is a BLOCKING function.
 *  @param    _fp  - pointer to the input stream
 *  @retval   on success, number of byte written
 *            on failure, EOF
 */
int   _fgetchar(FILE *_fp)
{
  int8_t c = EOF;

  if ( stderr == _fp )                // stderr on uart 1
  {
    while ( FALSE == Uart_UCA1_kbhit() )
    {
    }
    Uart_UCA1_getc( &c );           // get data from input from uart
  }
  else if ( stdin == _fp )            // all other from stdio on uart 0
  {
    while ( FALSE == Uart_UCA0_kbhit() )
    {
    }
    Uart_UCA0_getc( &c );           // get data from input from uart
    if ( TRUE == SerialEcho )
    {
      Uart_UCA0_putc( c );
    }
    else
    {
      _nop();
    }
  }
  else
  {
    c = EOF;
  }
  return(c);
}

int   _fkbhit(FILE *_fp)
{
  int8_t rval = EOF;

  if ( stderr == _fp )                // stderr on uart 1
  {
    rval = Uart_UCA1_kbhit();
  }
  else if ( stdin == _fp )            // all other from stdio on uart 0
  {
    rval = Uart_UCA0_kbhit();
  }
  else
  {
    rval = EOF;
  }
  return(rval);
}

/**
 *  @brief    Reads bytes from the input stream into an array.
 *            Reading stops on a newline character, or (n-1) bytes are input.
 *            The output string is NULL terminated.
 *  @param    _ptr - output array
 *  @param    _size- number of bytes in output array
 *  @param    _fp  - pointer to the input stream
 *  @retval   on success, _ptr is returned.
 *            on failure, _ptr is set to NULL.
 */
char  *_fgets(char *_ptr, int _size, FILE *_fp)
{
  int8_t  rVal = STATUS_BUSY;
  int     cnt = 0;
  int     c;
  char   *pDest;
  int   CR_Flag = FALSE;
  int   NL_Flag = FALSE;

  pDest = _ptr;                         // use local pointer
  memset(pDest,0,_size);                // clear the data
  do
  {
    c = _fgetchar( _fp );               // get the byte
    if ( EOF == c )                     // _fp(uart) not valid
    {
      rVal = STATUS_ERROR;
    }
    else
    {
      if ( cnt == (_size - 1) )
      {
        *pDest = 0;                     // Null terminate
        rVal = STATUS_OK;
      }

      if ('\r' == c)                 // '\r' = 0x0D = Carriage Return
      {
        CR_Flag = TRUE;
      }
      else if ('\n' == c)                 // '\n' = 0x0A = new line
      {
        NL_Flag = TRUE;
      }
      else
      {
        *pDest = c;
        pDest++;
        cnt++;
      }//end: if/else
    }//end:  if/else
    if ( (TRUE == CR_Flag) && (TRUE == NL_Flag))
    {
        pDest++;
        *pDest = 0;                     // Null terminate
        rVal = STATUS_OK;
    }
  }
  while( STATUS_BUSY == rVal );

  if (STATUS_ERROR == rVal)
  {
    _ptr = NULL;
  }
  return(_ptr);
}

// time out is in seconds
// need to fix so it sleeps between tests (100ms?)
/*
char *_fgets_tmo(char *_ptr, int _size, FILE *_fp, uint32_t tmo)
{
  uint16_t  ExitFlag = FALSE;
  uint16_t  CR_Flag = FALSE;
  uint16_t  NL_Flag = FALSE;
  uint16_t  TMO_Flag = FALSE;
  uint32_t  TimeOut = 0;
  int16_t   c = EOF;
  int16_t   cnt = 0;

  if ( 0 == tmo )
  {
    TMO_Flag = FALSE;
  }
  else
  {
    TMO_Flag = TRUE;
    TimeOut = RTC_GetPtr()->TotalSeconds + FGETS_TMO;
  }

  do
  {
    if ( TRUE == _fkbhit(_fp))            // wait for character
    {
      c = _fgetc(_fp);                    // get the byte
      if ( EOF == c )                     // _fp(uart) not valid
      {
        _ptr = NULL;
        ExitFlag = TRUE;
      }
      else if ('\r' == c)                 // '\r' = 0x0D = Carriage Return
      {
        CR_Flag = TRUE;                   // strip the \r
      }
      else if ('\n' == c)                 // '\n' = 0x0A = new line
      {
        NL_Flag = TRUE;                   // strip the \n
      }
      else
      {
        *_ptr = c;
        _ptr++;
        cnt++;
        if ( (_size-1) <= cnt )           // check for overrun
        {
          _ptr[_size-1] = 0;              // null terminate
          ExitFlag = TRUE;
        }
      }//end:  if/elseif/else
    }
    else if ((TRUE == TMO_Flag) && (RTC_GetPtr()->TotalSeconds > TimeOut))
    {
      _ptr = NULL;
      ExitFlag = TRUE;
    }
    else if ( (TRUE == CR_Flag) && (TRUE == NL_Flag))
    {
      *_ptr = 0;                     // Null terminate
      ExitFlag = TRUE;
    }
    else
    {
      _nop();
    }
  }while(FALSE == ExitFlag);
  return( _ptr );
}//end: char *fgets_tmo(char *_ptr, int _size, FILE *_fp)
*/
// == END OF FILE ==

