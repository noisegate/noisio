#ifndef __GPIOLIB_H__
#define __GPIOLIB_H__
extern void test(void);
extern int init(void);
extern int libinput(int pinnr);
extern int liboutput(int pinnr);
extern int libset(int pinnr);
extern int libclear(int pinnr);
extern int libget(int pinnr);
extern int libpullup(int pinnr);
extern int libpulldown(int pinnr);
extern int libpulloff(int pinnr);
extern int libirq(void);
extern int libstopirq(void);
extern void testpython(void);
#endif //__GPIOLIB_H__

