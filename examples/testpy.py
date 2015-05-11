import noisio
import time

class gpiotest(object):

    def __init__(self):
        noisio.initialize()

    def blink(self):
        while True:
            noisio.set(23)
            time.sleep(1)
            noisio.clear(23)
            time.sleep(1)

    def wait(self):
        noisio.pullup(24)
        while (noisio.get(24)==1):
            print "press da button.."
            time.sleep(1)

if __name__ == '__main__':
    instance = gpiotest()
    #instance.blink()
    instance.wait()
