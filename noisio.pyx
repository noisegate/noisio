cdef extern from "gpiolib.h":

    ctypedef void (*irqfunction)(void *f)

    struct thread_data:
        int id
        int pinnr
        int message
        irqfunction user_fun
        void *f

    void test()
    int init()
    int libinput(int pinnr)
    int liboutput(int pinnr)
    int libset(int pinnr)
    int libclear(int pinnr)
    int libget(int pinnr)
    int libed(int pinnr)
    int libpullup(int pinnr)
    int libpulldown(int pinnr)
    int libpulloff(int pinnr)
    int libfen(int pinnr)
    int libfed(int pinnr)
    int libren(int pinnr)
    int libred(int pinnr)
    int libhen(int pinnr)
    int libhed(int pinnr)
    int liblen(int pinnr)
    int libled(int pinnr)
    int libhysen()
    int libhysdis()
    int libslowen()
    int libfasten()
    void libirqcallback(irqfunction user_func, void *f, int pinnr)
    void libdelirqcallback(int pinnr)

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

def ed(pinnr):
    return libed(pinnr)

def pullup(pinnr):
    return libpullup(pinnr)

def pulldown(pinnr):
    return libpulldown(pinnr)

def pulloff(pinnr):
    return libpulloff(pinnr)

def fen(pinnr):
    return libfen(pinnr)

def fed(pinnr):
    return libfed(pinnr)

def ren(pinnr):
    return libren(pinnr)

def red(pinnr):
    return libred(pinnr)

def hen(pinnr):
    return libhen(pinnr)

def hed(pinnr):
    return libhed(pinnr)

def len(pinnr):
    return liblen(pinnr)

def led(pinnr):
    return libled(pinnr)

def hysen():
    return libhysen()

def hysdis():
    return libhysdis()

def slowen():
    return libslowen()

def fasten():
    return libfasten()

def irqcallback(f, pinnr):
    libirqcallback(callback, <void*>f, pinnr)

def delirqcallback(pinnr):
    libdelirqcallback(pinnr)

cdef void callback(void *f) with gil:
    (<object>f)()
