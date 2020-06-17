/* 
 * File:   LED.h
 * Author: 10158431
 *
 * Created on May 5, 2020, 8:50 PM
 */

#ifndef LED_H
#define	LED_H
#define LED1TRIS    TRISAbits.TRISA2
#define LED1LAT     LATAbits.LATA2
#define LED2TRIS    TRISAbits.TRISA0
#define LED2LAT     LATAbits.LATA0

void led_ConfigureLED(void);
void led_Bright(void);
void led_Dim(void);
void led_Off(void);
void led_Toggle(void);

#ifdef	__cplusplus
extern "C" {
#endif





#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

