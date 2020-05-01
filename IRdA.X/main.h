/* 
 * File:   main.h
 * Author: 10158431
 *
 * Created on April 29, 2020, 8:06 PM
 */

#ifndef MAIN_H
#define	MAIN_H

/* Constants -----------------------------------------------------------------*/
#define TRUE        1
#define FALSE       0
#define _XTAL_FREQ 16000000

/* Macro Definitions ---------------------------------------------------------*/
#define CHECKBIT(var,nbit)  (var &  (1L << (nbit)))

typedef enum
{
  STATUS_OK       = 0U,
  STATUS_ERROR    = 1U,
  STATUS_BUSY     = 2U,
  STATUS_TIMEOUT  = 3U,
  STATUS_COMPLETE = 4U
} Status_t;

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

