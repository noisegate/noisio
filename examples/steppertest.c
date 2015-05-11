#include "gpiolib.h"
#include "stdio.h"

void blink(void){
	int i;
	for(i=0;i<10;i++){
		printf("blink nr %i\n", i);
		libset(23);
		printf("LED ON\n");
		sleep(1);
		libclear(23);
		printf("LED OFF\n");
		sleep(1);
	}
}

void wait(void){
	printf("Press button on pin 24 to continue\n");
	while(libget(24)==1){
		printf("Not yet\n");
		printf("read @ 24: %i\n", libget(24));
		sleep(1);
	}
	printf("%i\n", libget(24));
}

void pullup(){
	libpullup(24);
}

int main(int argc, char *argv[]){
	printf("Demonstrating use of gpiolib\n");
	printf("In order for this demo to run proprely\n");
	printf("connect pin 23 to a LED (resistor in place &c)\n");
	printf("and 24 to a button\n");
	init();
	//blink();//blink like 10 times on pin 23
	pullup();
	wait();//wait till pin 24 is pressed ;)

	return 0;
}
