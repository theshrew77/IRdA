/* 
 * File:   Debug.h
 * Author: 10158431
 *
 * Created on April 29, 2020, 9:44 PM
 */

#ifndef DEBUG_H
#define	DEBUG_H

void      debug_init(void);
void      debug_deinit(void);
void      debug_out(const char *fmt, ...);
char     *debug_in( char *buf, uint16_t Len, uint32_t tmo );
int16_t   debug_kbhit(void);
uint16_t  debug_enable(void);
uint16_t  debug_disable(void);
uint16_t  debug_getstatus(void);
void      debug_flush(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */

