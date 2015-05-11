import noisio
import time

class Pololu(object):

    def __init__(self):
        



if __name__ == '__main__':
    noisio.initialize()
    noisio.set(24)
    noisio.clear(22)
    for j in range(5):
        noisio.set(24)
        for i in range(200):
            noisio.set(23)
            time.sleep(0.00000001)
            noisio.clear(23)
            time.sleep(.01)
        noisio.clear(24)    
        for i in range(200):
            noisio.set(23)
            time.sleep(0.00000001)
            noisio.clear(23)
            time.sleep(.01)
    
    noisio.set(22)#disable
