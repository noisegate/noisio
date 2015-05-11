import nio
import time

def f():
    #while here, state=low
    if (button.state): led.low
    else: led.high

if __name__ =='__main__':

    button = nio.Pin(24)
    button.input
    button.pullup
    button.falling_edge_detect_enable
    button.rising_edge_detect_enable
    button.low_level_detect_disable
    button.high_level_detect_disable
    button.noschmitt    
    #button.slow
    led = nio.Pin(22)
    led.output

    button.callback = f
    s=raw_input()
