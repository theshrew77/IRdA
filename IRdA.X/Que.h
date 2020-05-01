/* 
 * File:   Que.h
 * Author: 10158431
 *
 * Created on April 29, 2020, 8:03 PM
 */

#ifndef QUE_H
#define	QUE_H

#define Q_MAX   64

/* Data types ----------------------------------------------------------------*/
typedef struct {
  int8_t    Data[Q_MAX];
  int8_t    In;
  int8_t    Out;
} t_Q;

/* functions prototypes ------------------------------------------------------*/
int8_t  QInit( t_Q *pQ );
int8_t  QIn( int8_t Src, t_Q *pQ );
int8_t  QOut( int8_t *Dest, t_Q *pQ );
int8_t  QChkQ( t_Q *pQ );

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* QUE_H */

