#include <stdio.h>
#include <stdlib.h>
//#include "RPI.h"
#include "gpiolib.h"

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

	init();

	if ((pinnr<0)||(pinnr>30)){
		printf("wrong pinnr\n");
		return -1;
	}

	if (strcmp("set", argv[1])==0){
		printf("setting pin %i HIGH\n", pinnr);
		libset(pinnr);
	}

	if (strcmp("clr", argv[1])==0){
		printf("setting pin %i LOW\n",pinnr);
		libclear(pinnr);
	}

	if (strcmp("get",argv[1])==0){
		printf("getting pin %i\n",pinnr);
		printf("state: %i\n", libget(pinnr));
	}

	if (strcmp("up", argv[1])==0){
		printf("pin %i PULLUP mode\n", pinnr);
		libpullup(pinnr);
	}

	if (strcmp("down", argv[1])==0){
		printf("pin %i PULLDOWN mode\n", pinnr);
		libpulldown(pinnr);
	}

	if (strcmp("tri", argv[1])==0){
		printf("pin %i PULL OFF mode\n", pinnr);
		libpulloff(pinnr);
	}


	return 0;
}
