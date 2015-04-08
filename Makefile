all: gpio noisio.so testc

noisio.c: noisio.pyx
	cython noisio.pyx

gpiolib.o: gpiolib.c gpiolib.h 
	gcc -g -O2 -fpic -c gpiolib.c -o gpiolib.o -I.

noisio.o: noisio.c
	gcc -g -O2 -fpic -c noisio.c -o noisio.o `python-config --cflags`

noisio.so: gpiolib.o noisio.o RPI.o 
	gcc -shared -o noisio.so gpiolib.o noisio.o RPI.o `python-config --libs`

RPI.o: RPI.c RPI.h
	gcc -g -O2 -o RPI.o -c RPI.c -I.

gpio: gpio.c RPI.o
	gcc -o gpio gpio.c RPI.o

testc: testc.c gpiolib.o
	gcc -g -o testc testc.c gpiolib.o RPI.o -I.

clean: 
	rm gpio RPI.o
