import nio
import time

def f():
    led.toggle

if __name__ =='__main__':

    button = nio.Pin(24)
    button.input
    button.pullup
    button.falling_edge_detect_enable
    button.rising_edge_detect_disable
    button.schmitt    
    led = nio.Pin(22)
    led.output

    button.callback = f
    s=raw_input()
