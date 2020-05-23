/* 
 * File:   ccp_CCP1.h
 * Author: 10158431
 *
 * Created on May 22, 2020, 10:54 PM
 */

#ifndef CCP_CCP1_H
#define	CCP_CCP1_H
#define CCP_IE PIE6bits.CCP1IE
#define CCP1_IF PIR6bits.CCP1IF

void ccp_CCP1Init(void);
void ccp_CCP1En(void);
void ccp_CCP1Dis(void);
void ccp_CCP1CompareMatch(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CCP_CCP1_H */

