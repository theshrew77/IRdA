/* 
 * File:   RTC.h
 * Author: 10158431
 *
 * Created on May 29, 2020, 6:31 PM
 */

#ifndef RTC_H
#define	RTC_H

typedef struct
{
  uint8_t   Seconds;
  uint8_t   Minutes;
  uint8_t   Hours;
} RTC_t;

void rtc_Init(void);
void rtc_SetHourDelay(uint8_t hours);
void rtc_Reset(void);
void rtc_ISR(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

