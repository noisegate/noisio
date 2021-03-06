#ifndef __GPIOLIB_H__
#define __GPIOLIB_H__

	typedef void (*irqfunction)();

	extern struct thread_data{
		int id;
		int pinnr;
		int message;
		irqfunction user_fun;
		void *f;
	};

	extern void test(void);
	extern int init(void);
	extern int libinput(int pinnr);
	extern int liboutput(int pinnr);
	extern int libset(int pinnr);
	extern int libclear(int pinnr);
	extern int libget(int pinnr);
	extern int libed(int pinnr);
	extern int libpullup(int pinnr);
	extern int libpulldown(int pinnr);
	extern int libpulloff(int pinnr);
	extern int libfen(int pinnr);
	extern int libfed(int pinnr);
	extern int libren(int pinnr);
	extern int libred(int pinnr);
	extern int libhen(int pinnr);
	extern int libhed(int pinnr);
	extern int liblen(int pinnr);
	extern int libled(int pinnr);
	extern int libhysen();
	extern int libhysdis();
	extern int libslowen();
	extern int libfasten();
	extern void *irqthread(void *data);
	extern void libirqcallback(irqfunction user_func, void *f, int pinnr);
	extern void libdelirqcallback(int pinnr);
#endif //__GPIOLIB_H__
#define THREAD_MSG_EXIT 2
#define THREAD_MSG_REASSIGN 1

