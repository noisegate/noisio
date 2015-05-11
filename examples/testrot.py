import nio
import time

def f():
    #while here, state=low
    if (pinleft.state==0): 
        print "falling"
        if (pinleft.state==0):
            if (pinright.state): led.low
            else: led.high
    else:
        print "rising"

def g():
    print "bad stuff, right pin callback"


if __name__ =='__main__':

    pinleft = nio.Pin(24)
    pinright= nio.Pin(23)
    pinleft.input
    pinright.input
    pinleft.pulloff
    pinright.pulloff
    pinleft.high_level_detect_disable
    pinleft.low_level_detect_disable
    pinleft.falling_edge_detect_disable
    pinleft.rising_edge_detect_disable
    pinright.falling_edge_detect_disable
    pinright.rising_edge_detect_disable
    pinright.high_level_detect_disable
    pinright.low_level_detect_disable

   
    pinleft.rising_edge_detect_enable
    pinleft.falling_edge_detect_enable


    pinright.callback = g
    pinleft.schmitt
    pinleft.slow
    led = nio.Pin(22)
    led.output

    pinleft.callback = f
    s=raw_input()
