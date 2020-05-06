/* 
 * File:   PowerManagement.h
 * Author: 10158431
 *
 * Created on May 5, 2020, 8:44 PM
 */

#ifndef POWERMANAGEMENT_H
#define	POWERMANAGEMENT_H

#ifdef	__cplusplus
extern "C" {
#endif

    void pwrmgmt_DisablePeripherals(void);
    void pwrmgmt_ConfigUnusedPins(void);


#ifdef	__cplusplus
}
#endif

#endif	/* POWERMANAGEMENT_H */

