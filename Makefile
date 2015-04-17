all: RPI.o gpiolib.o noisio.so  

noisio.c: noisio.pyx
	cython noisio.pyx

gpiolib.o: gpiolib.c gpiolib.h 
	gcc -g -O2 -fpic -c gpiolib.c -o gpiolib.o -pthread -I. -I/usr/include/python2.7/ -lpython2.7

noisio.o: noisio.c
	gcc -g -O2 -fpic -c noisio.c -o noisio.o `python-config --cflags`

noisio.so: gpiolib.o noisio.o RPI.o 
	gcc -shared -o noisio.so gpiolib.o noisio.o RPI.o `python-config --libs`

RPI.o: RPI.c RPI.h
	gcc -g -O2 -o RPI.o -c RPI.c -I.

noiseclio: noiseclio.c RPI.o gpiolib.o
	gcc -g -o noiseclio noiseclio.c RPI.o gpiolib.o -pthread -I.

testc: testc.c gpiolib.o
	gcc -g -o testc testc.c gpiolib.o RPI.o -I.

clean: 
	rm gpiolib.o noisio.o noisio.so noisio.c RPI.o
