cdef extern from "gpiolib.h":
    void test()
    int init()
    int libinput(int pinnr)
    int liboutput(int pinnr)
    int libset(int pinnr)
    int libclear(int pinnr)
    int libget(int pinnr)
    int libpullup(int pinnr)
    int libpulldown(int pinnr)
    int libpulloff(int pinnr)
    int libirq()
    int libstopirq()
    void testpython()

def testme():
    test()

def initialize():
    return init()

def input(pinnr):
    return libinput(pinnr)

def output(pinnr):
    return liboutput(pinnr)

def set(pinnr):
    return libset(pinnr)

def clear(pinnr):
    return libclear(pinnr)

def get(pinnr):
    return libget(pinnr)

def pullup(pinnr):
    return libpullup(pinnr)

def pulldown(pinnr):
    return libpulldown(pinnr)

def pulloff(pinnr):
    return libpulloff(pinnr)

def irq():
    return libirq()

def stopirq():
    return libstopirq()

def python():
    testpython()
