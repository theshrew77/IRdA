/* 
 * File:   Retarget.h
 * Author: 10158431
 *
 * Created on April 29, 2020, 8:11 PM
 */

#ifndef RETARGET_H
#define	RETARGET_H

int16_t SetSerialEcho( int16_t val );

int fputc(int _c, register FILE *_fp);
int fputs(const char *_ptr, register FILE *_fp);

int   _fkbhit(FILE *_fp);
int   _fgetc(FILE *_fp);
char  *_fgets(char *_ptr, int _size, FILE *_fp);
char  *_fgets_tmo(char *_ptr, int _size, FILE *_fp, uint32_t tmo);

int   _fflush(FILE *_fp);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* RETARGET_H */

