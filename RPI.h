//using stuff from pieter-jan
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//datasheetBCM2835 page 89...
//
#define RPI2
#ifdef RPI2
	#define GPIO_BASE 		0x3f200000
	#define BCM2708_PERI_BASE	0x3f000000
	#define GPIO_PAD		0x3f100000
#else
	#define BCM2708_PERI_BASE	0x20000000
	#define GPIO_BASE		0x20200000
	#define GPIO_PAD 		0x20100000
#endif

#define GPEDS0			0x00000040
#define GPEDS1			0x00000044
#define GPREN0                  0x0000004c
#define GPREN1			0x00000050
#define GPFEN0			0x00000058
#define GPFEN1			0x0000005c
#define GPHEN0			0x00000064
#define GPHEN1			0x00000068
#define GPPUD			0x00000094
#define GPPUDCLK0		0x00000098
#define GPPUDCLK1		0x0000009c

#define GPPADS0			0x0000002c

#define BLOCK_SIZE		(4*1024)

struct bcm2835_peripheral {
	unsigned long addr_p;
	int mem_fd;
	void *map;
	volatile unsigned int *addr;
};

//struct bcm2835_peripheral gpio = {_BASE};

extern struct bcm2835_peripheral gpio;
extern struct bcm2835_peripheral gpioctrl;

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
#define GPIO_GPEDS0 *(gpio.addr + 0x40/4)
#define GPIO_GPEDS1 *(gpio.addr + 0x44/4)
#define GPIO_GPFEN0 *(gpio.addr + GPFEN0/4)
#define GPIO_GPFEN1 *(gpio.addr + GPFEN1/4)
#define GPIO_GPREN0 *(gpio.addr + GPREN0/4)
#define GPIO_GPREN1 *(gpio.addr + GPREN1/4)
#define GPIO_GPHEN0 *(gpio.addr + GPHEN0/4)
#define GPIO_GPHEN1 *(gpio.addr + GPHEN1/4)

#define GPIOCTRL_PADS0 *(gpioctrl.addr + GPPADS0/4)

