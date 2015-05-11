cython noisio.pyx
gcc -g -O2 -o RPI.o -c RPI.c -I.
gcc -g -O2 -fpic -c gpiolib.c -o gpiolib.o -I.
gcc -g -O2 -fpic -c noisio.c -o noisio.o `python-config --cflags`
gcc -shared -o noisio.so gpiolib.o noisio.o RPI.o `python-config --libs`
sudo chown root:root noisio.so
sudo chmod u+s noisio.so

