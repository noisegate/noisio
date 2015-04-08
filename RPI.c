#include "RPI.h"

struct bcm2835_peripheral gpio = {GPIO_BASE};

int map_peripheral(struct bcm2835_peripheral *p) {
	//Open /dev/mem
	if ((p->mem_fd = open("/dev/mem", O_RDWR|O_SYNC))<0) {
		printf("Failed to open /dev/mem, try checking permissions.\n");
		return -1;
	}

	p->map = mmap(
			NULL,
			BLOCK_SIZE,
			PROT_READ|PROT_WRITE,
			MAP_SHARED,
			p->mem_fd,
			p->addr_p
		     );

	if (p->map == MAP_FAILED) {
		perror("mmap");
		return -1;
	}

	p->addr = (volatile unsigned int *)p->map;

	return 0;
}

void unmap_peripheral(struct bcm2835_peripheral *p) {
	munmap(p->map, BLOCK_SIZE);
	close(p->mem_fd);
}

