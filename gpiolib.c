#include "RPI.h"
#include "gpiolib.h"
#include <unistd.h>
#include <pthread.h>

//usersruff
//yi

void test(){
	printf("This is a simple test, Hello World from c\n");
}

int init(){
	//for the cyhton implementation
	//use python to check if the init was done
	if (map_peripheral(&gpio) == -1){
		printf ("Failed to map physical GPIO regzz to virt mem\n");
		return -1;
	}
	return 0;
}

int libinput(int pinnr){
	INP_GPIO(pinnr);
	return 0;
}

int liboutput(int pinnr){
	INP_GPIO(pinnr);
	OUT_GPIO(pinnr);
	return 0;
}

int libset(int pinnr){
	INP_GPIO(pinnr);
	OUT_GPIO(pinnr);
	GPIO_SET = 1 << pinnr;
	return 0;
}

int libclear(int pinnr){
	INP_GPIO(pinnr);
	OUT_GPIO(pinnr);
	GPIO_CLR = 1 << pinnr;
	return 0;
}

int libget(int pinnr){
	//what a waste to int this
	//but anyway...
	INP_GPIO(pinnr);
	if ((int)(GPIO_READ(pinnr))==(int)(1<<pinnr)){
		return 1;
	}else
		return 0;

}

int libpullup(int pinnr){
	if (pinnr<33){
		GPIO_PUD = 0b00000000000000000000000000000010;
		sleep(1);
		GPIO_PUDCLK0 = 1<<pinnr;
		sleep(1);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK0 = 1<<pinnr;
	}else{
		//this might be totaly wrong...
		GPIO_PUD = 0b00000000000000000000000000000010;
		sleep(1);
		GPIO_PUDCLK1 = 1<<pinnr;
		sleep(1);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK1 = 1<<pinnr;
	}
}

int libpulldown(int pinnr){
	if (pinnr<33){
		GPIO_PUD = 0b00000000000000000000000000000001;
		usleep(150);
		GPIO_PUDCLK0 = 1<<pinnr;
		usleep(150);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK0 = 1<<pinnr;
	}else{
		//this might be totaly wrong...
		GPIO_PUD = 0b00000000000000000000000000000001;
		usleep(150);
		GPIO_PUDCLK1 = 1<<pinnr;
		usleep(150);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK1 = 1<<pinnr;
	}
}

int libpulloff(int pinnr){
	if (pinnr<33){
		GPIO_PUD = 0b00000000000000000000000000000000;
		usleep(150);
		GPIO_PUDCLK0 = 1<<pinnr;
		usleep(150);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK0 = 1<<pinnr;
	}else{
		//this might be totaly wrong...
		GPIO_PUD = 0b00000000000000000000000000000000;
		usleep(150);
		GPIO_PUDCLK1 = 1<<pinnr;
		usleep(150);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK1 = 1<<pinnr;
	}
}

void *Threadtest(void *threadid){
	//long i = (long) threadid;i
	int i;
	for(;;){//while((long)threadid==0)
		//i = (long) threadid;
		printf("button state %i and id = %i\n", libget(24), 1);
		//if (threadid==1) goto stopthis;
		usleep(2000000);
	}
	pthread_exit(NULL);
}

int libirq(){
	int rc;
	long t;
	pthread_t thread;
	rc = pthread_create(&thread, NULL, Threadtest, (void *)t);
	if (rc){
		printf("ERROR");
		exit(-1);
	}
	//pthread_exit(NULL);
	return 0;
}

int libstopirq(){
	return 0;
}

void *irqthread(void *data){
	struct thread_data *my_data;
	irqfunction usr_fn;
	void* f;

	my_data = (struct thread_data *)data;
	usr_fn = (irqfunction)my_data->user_fun;
	f = my_data->f;

	for (;;){
		usleep(1000);
		if (libget(24)==0)
			usr_fn(f);
	}
	pthread_exit(NULL);
}

void libirqcallback(irqfunction user_func, void *f){
	int rc;
	long id;
	printf("in callbackfctn: usr_fun %p  f=%p\n", user_func, f);

	user_func(f);
	//pthread_t thread;
	mythreaddata.id = 1;
	mythreaddata.user_fun = user_func;
	mythreaddata.f = f;
	rc=pthread_create(&thread, NULL, irqthread, (void*)&mythreaddata);
	//pthread_exit(NULL);
}

