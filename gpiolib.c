#include "RPI.h"
#include "gpiolib.h"

//usersruff
//yih
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
		sleep(1);
		GPIO_PUDCLK0 = 1<<pinnr;
		sleep(1);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK0 = 1<<pinnr;
	}else{
		//this might be totaly wrong...
		GPIO_PUD = 0b00000000000000000000000000000001;
		sleep(1);
		GPIO_PUDCLK1 = 1<<pinnr;
		sleep(1);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK1 = 1<<pinnr;
	}
}

int libpulloff(int pinnr){
	if (pinnr<33){
		GPIO_PUD = 0b00000000000000000000000000000000;
		sleep(1);
		GPIO_PUDCLK0 = 1<<pinnr;
		sleep(1);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK0 = 1<<pinnr;
	}else{
		//this might be totaly wrong...
		GPIO_PUD = 0b00000000000000000000000000000000;
		sleep(1);
		GPIO_PUDCLK1 = 1<<pinnr;
		sleep(1);
		GPIO_PUD = 0b00000000000000000000000000000000;
		GPIO_PUDCLK1 = 1<<pinnr;
	}
}


