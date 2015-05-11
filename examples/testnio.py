import nio

button = nio.Pin(24)

button.input
button.pullup
button.falling_edge_detect_enable

def f():
    print "you have pressed a button"

button.callback = f



