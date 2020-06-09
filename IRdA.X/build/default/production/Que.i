
# 1 "Que.c"

# 4 "C:\Program Files (x86)\Microchip\xc8\v2.10\pic\include\__size_t.h"
typedef unsigned size_t;

# 7 "C:\Program Files (x86)\Microchip\xc8\v2.10\pic\include\c90\stdarg.h"
typedef void * va_list[1];

#pragma intrinsic(__va_start)
extern void * __va_start(void);

#pragma intrinsic(__va_arg)
extern void * __va_arg(void *, ...);

# 43 "C:\Program Files (x86)\Microchip\xc8\v2.10\pic\include\c90\stdio.h"
struct __prbuf
{
char * ptr;
void (* func)(char);
};

# 29 "C:\Program Files (x86)\Microchip\xc8\v2.10\pic\include\c90\errno.h"
extern int errno;

# 12 "C:\Program Files (x86)\Microchip\xc8\v2.10\pic\include\c90\conio.h"
extern void init_uart(void);

extern char getch(void);
extern char getche(void);
extern void putch(char);
extern void ungetch(char);

extern __bit kbhit(void);

# 23
extern char * cgets(char *);
extern void cputs(const char *);

# 88 "C:\Program Files (x86)\Microchip\xc8\v2.10\pic\include\c90\stdio.h"
extern int cprintf(char *, ...);
#pragma printf_check(cprintf)



extern int _doprnt(struct __prbuf *, const register char *, register va_list);


# 180
#pragma printf_check(vprintf) const
#pragma printf_check(vsprintf) const

extern char * gets(char *);
extern int puts(const char *);
extern int scanf(const char *, ...) __attribute__((unsupported("scanf() is not supported by this compiler")));
extern int sscanf(const char *, const char *, ...) __attribute__((unsupported("sscanf() is not supported by this compiler")));
extern int vprintf(const char *, va_list) __attribute__((unsupported("vprintf() is not supported by this compiler")));
extern int vsprintf(char *, const char *, va_list) __attribute__((unsupported("vsprintf() is not supported by this compiler")));
extern int vscanf(const char *, va_list ap) __attribute__((unsupported("vscanf() is not supported by this compiler")));
extern int vsscanf(const char *, const char *, va_list) __attribute__((unsupported("vsscanf() is not supported by this compiler")));

#pragma printf_check(printf) const
#pragma printf_check(sprintf) const
extern int sprintf(char *, const char *, ...);
extern int printf(const char *, ...);

# 13 "C:\Program Files (x86)\Microchip\xc8\v2.10\pic\include\c90\stdint.h"
typedef signed char int8_t;

# 20
typedef signed int int16_t;

# 28
typedef __int24 int24_t;

# 36
typedef signed long int int32_t;

# 52
typedef unsigned char uint8_t;

# 58
typedef unsigned int uint16_t;

# 65
typedef __uint24 uint24_t;

# 72
typedef unsigned long int uint32_t;

# 88
typedef signed char int_least8_t;

# 96
typedef signed int int_least16_t;

# 109
typedef __int24 int_least24_t;

# 118
typedef signed long int int_least32_t;

# 136
typedef unsigned char uint_least8_t;

# 143
typedef unsigned int uint_least16_t;

# 154
typedef __uint24 uint_least24_t;

# 162
typedef unsigned long int uint_least32_t;

# 181
typedef signed char int_fast8_t;

# 188
typedef signed int int_fast16_t;

# 200
typedef __int24 int_fast24_t;

# 208
typedef signed long int int_fast32_t;

# 224
typedef unsigned char uint_fast8_t;

# 230
typedef unsigned int uint_fast16_t;

# 240
typedef __uint24 uint_fast24_t;

# 247
typedef unsigned long int uint_fast32_t;

# 268
typedef int32_t intmax_t;

# 282
typedef uint32_t uintmax_t;

# 289
typedef int16_t intptr_t;




typedef uint16_t uintptr_t;

# 15 "C:\Program Files (x86)\Microchip\xc8\v2.10\pic\include\c90\stdbool.h"
typedef unsigned char bool;

# 14 "C:\Program Files (x86)\Microchip\xc8\v2.10\pic\include\c90\string.h"
extern void * memcpy(void *, const void *, size_t);
extern void * memmove(void *, const void *, size_t);
extern void * memset(void *, int, size_t);




extern void * __builtin_memcpy(void *, const void *, size_t);
#pragma intrinsic(__builtin_memcpy)

# 36
extern char * strcat(char *, const char *);
extern char * strcpy(char *, const char *);
extern char * strncat(char *, const char *, size_t);
extern char * strncpy(char *, const char *, size_t);
extern char * strdup(const char *);
extern char * strtok(char *, const char *);


extern int memcmp(const void *, const void *, size_t);
extern int strcmp(const char *, const char *);
extern int stricmp(const char *, const char *);
extern int strncmp(const char *, const char *, size_t);
extern int strnicmp(const char *, const char *, size_t);
extern void * memchr(const void *, int, size_t);
extern size_t strcspn(const char *, const char *);
extern char * strpbrk(const char *, const char *);
extern size_t strspn(const char *, const char *);
extern char * strstr(const char *, const char *);
extern char * stristr(const char *, const char *);
extern char * strerror(int);
extern size_t strlen(const char *);
extern char * strchr(const char *, int);
extern char * strichr(const char *, int);
extern char * strrchr(const char *, int);
extern char * strrichr(const char *, int);

# 19 "main.h"
typedef enum{
OFF = 0,
ON = 1,
}status_t;


# 37
#pragma config CP = OFF

#pragma config FEXTOSC = OFF
#pragma config RSTOSC = HFINT1
#pragma config CLKOUTEN = OFF
#pragma config CSWEN = ON
#pragma config FCMEN = OFF


#pragma config MCLRE = ON
#pragma config PWRTE = OFF
#pragma config WDTE = OFF
#pragma config LPBOREN = OFF
#pragma config BOREN = OFF
#pragma config BORV = LOW
#pragma config PPS1WAY = ON
#pragma config STVREN = ON
#pragma config DEBUG = OFF


#pragma config WRT = OFF
#pragma config LVP = OFF


#pragma config CP = OFF
#pragma config CPD = OFF

# 14 "Que.h"
typedef struct {
int8_t Data[2];
int8_t In;
int8_t Out;
} t_Q;


int8_t QInit( t_Q *pQ );
int8_t QIn( int8_t Src, t_Q *pQ );
int8_t QOut( int8_t *Dest, t_Q *pQ );
int8_t QChkQ( t_Q *pQ );

# 27 "Que.c"
int8_t QInit( t_Q *pQ )
{
int16_t i;
pQ->In = 0;
pQ->Out = 0;
for (i=0;i<2; i++)
{
pQ->Data[i] = 0;
}
return(1);
}

# 58
int8_t QIn( int8_t Src, t_Q *pQ )
{
int8_t next;

next = (pQ->In + 1) % 2;
if ( next == pQ->Out )
{
next = -1;
}
else
{
pQ->In = next;
pQ->Data[pQ->In] = Src;
}
return(next);
}

# 95
int8_t QOut( int8_t *Dest, t_Q *pQ )
{
if ( pQ->Out == pQ->In ) {
return( 0 );
}
pQ->Out++;
pQ->Out = pQ->Out % 2;
*Dest = pQ->Data[pQ->Out];
return( 1 );
}

# 125
int8_t QChkQ( t_Q *pQ )
{
if ( pQ->Out == pQ->In )
{
return( 0 );
}
else
{
return( 1 );
}
}
