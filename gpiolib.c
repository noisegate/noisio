#include "RPI.h"
#include "gpiolib.h"
#include <unistd.h>
#include <pthread.h>

//usersruff
//yi
/* Noisegates GERT & DOM-way lib for cython
 *
 */


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

int libfen(int pinnr){
	//falling edge detect enable...
	GPIO_GPFEN0 = 1<<pinnr;
	return 0;
}

int libfed(int pinnr){
	GPIO_GPFEN0 = 0b00000000000000000000000000000000;
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
		if (libed(pinnr)==1){
			usr_fn(f);
			GPIO_GPEDS0 |= (1<<pinnr);//clear flag
		}
		usleep(1000);
	}
	pthread_exit(NULL);
}

void libirqcallback(irqfunction user_func, void *f, int pinnr){
	int rc;
	long id;
	static count = 0;

	count++;

	if (count>1){
		printf ("No more pins!!\n");
		return;
	}	
	mythreaddata.id = 1;
	mythreaddata.pinnr = pinnr;
	mythreaddata.user_fun = user_func;
	mythreaddata.f = f;
	rc=pthread_create(&thread, NULL, irqthread, (void*)&mythreaddata);
	//pthread_exit(NULL);
}

