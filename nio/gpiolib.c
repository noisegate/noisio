#include "RPI.h"
#include "gpiolib.h"
#include <unistd.h>
#include <pthread.h>

//usersruff
//yi
/* Noisegates GERT & DOM-way lib for cython
 *
 */
pthread_t thread[32];//for tha moment
struct thread_data mythreaddata[32];

void test(){
	printf("This is a simple test, Hello World from c\n");
	printf("contents of GPEDS0/1: %i, %i\n", GPIO_GPEDS0, GPIO_GPEDS1);
	GPIO_GPEDS0 = 1<<24;

}

int init(){
	//for the cyhton implementation
	//use python to check if the init was done
	if (map_peripheral(&gpio) == -1){
		printf ("Failed to map physical GPIO regzz to virt mem\n");
		return -1;
	}
	if (map_peripheral(&gpioctrl)){
		printf("Failed to map GPIO control pads to v meme\n");	
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

int libed(int pinnr){
	//read teh event detect register
	//ed = event detect
	if((GPIO_GPEDS0 & (1<<pinnr))==(1<<pinnr))
		return 1;
	else
		return 0;
}

int libpullup(int pinnr){
	if (pinnr<33){
		GPIO_PUD = 0b00000000000000000000000000000010;
		usleep(150);
		GPIO_PUDCLK0 = 1<<pinnr;
		usleep(150);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK0 = 1<<pinnr;
	}else{
		//this might be totaly wrong...
		GPIO_PUD = 0b00000000000000000000000000000010;
		usleep(150);
		GPIO_PUDCLK1 = 1<<pinnr;
		usleep(150);
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

int libfen(int pinnr){
	//Falling Edge detect eNable...
	GPIO_GPFEN0 |= (1<<pinnr);
	return 0;
}

int libfed(int pinnr){
	//Falling Edge detect Disable
	GPIO_GPFEN0 &= ~(1<<pinnr);
	return 0;
}

int libren(int pinnr){
	//Rising Edge detect Enable
	GPIO_GPREN0 |=(1<<pinnr);
	return 0;
}

int libred(int pinnr){
	//Rising Edge detect Disable
	GPIO_GPREN0 &= ~(1<<pinnr);
	return 0;
}

int libhen(int pinnr){
	//
	GPIO_GPHEN0 |=(1<<pinnr);
	return 0;
}

int libhed(int pinnr){
	//
	GPIO_GPHEN0 &=~(1<<pinnr);
	return 0;
}

int liblen(int pinnr){
	//enable low detect
	GPIO_GPLEN0 |=(1<<pinnr);
	return 0;
}

int libled(int pinnr){
	//enable low detect
	GPIO_GPLEN0 &=~(1<<pinnr);
	return 0;
}

int libhysen(){
	GPIOCTRL_PADS0 = (0xff<24);//clear 8 msb
	GPIOCTRL_PADS0 &= (0x5a<<24);//set passwd
	GPIOCTRL_PADS0 |=(1<<3);
	return 0;
}

int libhysdis(){
	GPIOCTRL_PADS0 = (0xff<24);//clear 8 msb
	GPIOCTRL_PADS0 &= (0x5a<<24);//set passwd
	GPIOCTRL_PADS0 &=(0b11111111111111111111111111110111);
	return 0;
}

int libslowen(){
	GPIOCTRL_PADS0 = (0xff<24);//clear 8 msb
	GPIOCTRL_PADS0 &= (0x5a<<24);//set passwd
	GPIOCTRL_PADS0 |=(1<<4);
	return 0;
}

int libfasten(){
	GPIOCTRL_PADS0 = (0xff<24);//clear 8 msb
	GPIOCTRL_PADS0 &= (0x5a<<24);//set passwd
	GPIOCTRL_PADS0 &=~(1<<4);
	return 0;
}

void *irqthread(void *data){
	struct thread_data *my_data;
	int pinnr;
	irqfunction usr_fn;
	void* f;

	my_data = (struct thread_data *)data;
	pinnr = my_data->pinnr;
	usr_fn = (irqfunction)my_data->user_fun;
	f = my_data->f;

	for (;;){
		if (my_data->message!=0){
			if (my_data->message==THREAD_MSG_REASSIGN){
				f = my_data->f;
				my_data->message = 0;
			}
			if (my_data->message==THREAD_MSG_EXIT) goto threadexit;
		}else{
			if (libed(pinnr)==1){
				usr_fn(f);
				GPIO_GPEDS0 |= (1<<pinnr);//clear flag
			}
			usleep(10);
		}
	}
threadexit:	
	pthread_exit(NULL);
}

void libdelirqcallback(int pinnr){
	int i;
	mythreaddata[pinnr].id =0;//free it up
	mythreaddata[pinnr].message = THREAD_MSG_EXIT;
}

void libirqcallback(irqfunction user_func, void *f, int pinnr){
	int rc;
	long id;
	int i;

	if ((pinnr<0)||(pinnr>32)){
		printf ("FATAL:Illegal pinnr!!\n");
		return;
	}	
	
	if (mythreaddata[pinnr].id == 1){
		mythreaddata[pinnr].f = f;
		mythreaddata[pinnr].message=THREAD_MSG_REASSIGN;
		return;
	}

	mythreaddata[pinnr].id = 1;
	mythreaddata[pinnr].pinnr = pinnr;
	mythreaddata[pinnr].message = 0;
	mythreaddata[pinnr].user_fun = user_func;
	mythreaddata[pinnr].f = f;
	rc=pthread_create(&thread[pinnr], NULL, irqthread, (void*)&mythreaddata[pinnr]);
	//pthread_exit(NULL);
}

