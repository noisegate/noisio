#include <stdio.h>
#include <stdlib.h>
#include "RPI.h"

char *p;
int pinnr;

int main(int argc, char *argv[]){
	if (argc == 3){
		printf("Received %i arguments, OK!\n", argc);
	 	pinnr  = (int)strtol(argv[2], &p, 10);
	}
	else{
		printf("Wrong nr. of arguments\n");
		return -1;
	}

	if ((pinnr<0)||(pinnr>30)){
		printf("wrong pinnr\n");
		return -1;
	}

	if (map_peripheral(&gpio) == -1){
		printf("Failed to map the physical GPIO registers into vm mem.\n");
		return -1;
	}

	if (strcmp("set", argv[1])==0){
		printf("setting pin %i HIGH\n", pinnr);
		INP_GPIO(pinnr);
		OUT_GPIO(pinnr);
		GPIO_SET = 1 << pinnr;
	}

	if (strcmp("clr", argv[1])==0){
		printf("setting pin %i LOW\n",pinnr);
		INP_GPIO(pinnr);
		OUT_GPIO(pinnr);
		GPIO_CLR = 1 << pinnr;
	}

	if (strcmp("get",argv[1])==0){
		printf("getting pin %i\n",pinnr);
		INP_GPIO(pinnr);
		//OUT_GPIO(pinnr);
		printf("state: %i\n", GPIO_READ(pinnr));
	}

	return 0;
}
