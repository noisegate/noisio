import nio
import time

if __name__ == '__main__':

    led = nio.Pin(23)

    led.output
    led.high
    time.sleep(2)
    led.low
