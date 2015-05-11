import nio
import time

if __name__ == '__main__':

    led = nio.Pin(23)
    button = nio.Pin(24)

    led.output
    button.input
    button.pullup

    print nio.Pin.pins()

    while(1):
        if (button.state==0):
            led.high
        else:
            led.low
        time.sleep(0.2)
