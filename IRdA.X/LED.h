/* 
 * File:   LED.h
 * Author: 10158431
 *
 * Created on May 5, 2020, 8:50 PM
 */

#ifndef LED_H
#define	LED_H
#define LEDTRIS TRISAbits.TRISA2
#define LEDLAT  LATAbits.LATA2

void led_ConfigureLED(void);
void led_Blink(uint8_t times);


#ifdef	__cplusplus
extern "C" {
#endif





#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

