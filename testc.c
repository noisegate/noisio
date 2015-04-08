#include "gpiolib.h"
#include "stdio.h"
#include <unistd.h>

double currang = 0.0;//current angle

void enable(){
	libclear(22);
}

void disable(){
	libset(22);
}

void dir(int dir){
	if (dir==0)
		libset(24);
	if (dir==1)
		libclear(24);
}

void step(){
	libset(23);
	usleep(1);
	libclear(23);
}

void gotoangle(double angle){
	double da;
	int i, steps;

	da = angle-currang;
	if (da<0){
		dir(1);
		da = -da;
	}else{
		dir(0);
	}

	steps = (int)(da/360.0 * 200);
	
	enable();
	for (i=0;i<steps;i++){
		step();
		usleep(20000);
	}
	disable();
	currang = angle;
}

void reset(){
	currang =0.0;
}

int main(int argc, char *argv[]){
	int i;
	double angle;

	printf("Demonstrating use of gpiolib with pololu 49888\n");
	printf("connect pin 22 to /enable\n");
	printf("connect pin 23 to stel\n");
	printf("connect pin 24 to dir\n");
	init();
  	for (;;){	
		printf("enter an angle:");
		scanf("%lf", &angle);
		printf("%f\n", angle);
		gotoangle(angle);
	}
	return 0;
}
