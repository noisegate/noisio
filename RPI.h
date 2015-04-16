//using stuff from pieter-jan
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//datasheetBCM2835 page 89...
//
#define BCM2708_PERI_BASE	0x3f000000
#define GPIO_BASE		0x3f200000
//#define GPIO_PUD		0x00000094
//#define GPIO_PUDCLK0		0x00000098
//#define GPIO_PUDCLK1		0x0000009c

#define BLOCK_SIZE		(4*1024)

struct bcm2835_peripheral {
	unsigned long addr_p;
	int mem_fd;
	void *map;
	volatile unsigned int *addr;
};

//struct bcm2835_peripheral gpio = {_BASE};

extern struct bcm2835_peripheral gpio;

int map_peripheral(struct bcm2835_peripheral *p);
void unmap_peripheral(struct bcm2835_peripheral *p);
// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x)
#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET  *(gpio.addr + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR  *(gpio.addr + 10) // clears bits which are 1 ignores bits which are 0
 
#define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))
//page 100-101
#define GPIO_PUD *(gpio.addr + 37) //0x94 offset PUD register /4 = 37decimal (32int=4bytes)
#define GPIO_PUDCLK0 *(gpio.addr + 0x98/4)
#define GPIO_PUDCLK1 *(gpio.addr + 0x9c/4)
