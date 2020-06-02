/* 
 * File:   DAC.h
 * Author: 10158431
 *
 * Created on June 1, 2020, 9:21 PM
 */

#ifndef DAC_H
#define	DAC_H
#define DAC_EN      DACCON0bits.DAC1EN
#define DAC_OE      DACCON0bits.DAC1OE
#define DAC_VP_SEL  DACCON0bits.DAC1PSS
#define DAC_VN_SEL  DACCON0bits.DAC1NSS
#define DAC_MAX     0x1C //not actual DAQ max but make for 4 intervals of 7
#define DAC_MIN     0x00
void dac_DAClevelChange(char direction);
void dac_DACInit(void);
void dac_DACEn(void);
void dac_DACDis(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DAC_H */

