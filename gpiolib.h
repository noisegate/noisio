#ifndef __GPIOLIB_H__
#define __GPIOLIB_H__
extern void test(void);
extern int init(void);
extern int libset(int pinnr);
extern int libclear(int pinnr);
extern int libget(int pinnr);
extern int libpullup(int pinnr);
extern int libpulldown(int pinnr);
extern int libpulloff(int pinnr);
#endif //__GPIOLIB_H__

