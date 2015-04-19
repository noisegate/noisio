"""
   High level interface for noisegate gpio lib

    

"""

import noisio

class Uniton(type):
    #__instance = None
    def __init__(self, *args, **kwargs):
        self.__instance = None
        super(Uniton, self).__init__(*args, **kwargs)

    def __call__(cls, *args, **kwargs):
        if cls.__instance is None:
            cls.__instance = super(Uniton, cls).__call__(*args, **kwargs)
            #cls.__instance.setup()
            noisio.initialize()
        else:
            cls.__instance = super(Uniton, cls).__call__(*args, **kwargs)
        cls.instances.append(cls.__instance)
        return cls.__instance

class Pin(object):

    __metaclass__ = Uniton

    instances=[]

    def __init__(self, nr):
        self.nr = nr
        self._io = None
        self._state = None
        self._pud = None
        self._re = ""
        self._fe = ""
        self._callbackfun = None
        self._interrupt = None

    @classmethod
    def pins(cls):
        for i in cls.instances:
            print i

    def __repr__(self):

        message = """
                      Pin Object Status:
                      Pin Nr:                  {0}
                      Pin communication:       {1}
                      Pin sate:                {2}
                      Pin PUD:                 {3}
                      Pin Schmidt:             {4}
                      Pin Alternate functions: {5}
                      Pin Events:              {6}
                      Pin interrupt:           {7}
                      Pin callback functions:  {8}
                   """
        return message.format(
                                self.nr, 
                                self._io, 
                                self._state, 
                                self._pud,
                                "NIY",
                                "NIY",
                                ", ".join([self._re,self._fe]),
                                self._interrupt,
                                self._callbackfun)

    @property
    def input(self):
        self._io = "input"
        noisio.input(self.nr)

    @property
    def output(self):
        self._io = "output"
        noisio.output(self.nr)

    @property
    def high(self):
        if (self._io == "output"):
            noisio.set(self.nr)
            self._state = "high"
        else:
            raise RuntimeError("trying to set pin {0} high, while it is not set as output".format(self.nr))

    @property
    def low(self):
        if (self._io == "output"):
            noisio.clear(self.nr)
            self._state = "low"
        else:
            raise RuntimeError("trying to set pin {0} high, while it is not set as output".format(self.nr))
    
    @property
    def pullup(self):
        self._pud = "Pull Up"
        noisio.pullup(self.nr)

    @property
    def pulldown(self):
        self._pud = "Pull Down"
        noisio.pulldown(self.nr)

    @property
    def falling_edge_detect_enable(self):
        self._fe = "Falling edge detect"
        noisio.fen(self.nr)

    @property
    def rising_edge_detect_enable(self):
        self._re = "Rising edge detect"
        noisio.ren(self.nr)

    @property
    def falling_edge_detect_disable(self):
        self._fe= " "
        noisio.fed(self.nr)

    @property
    def rising_edge_detect_disable(self):
        self._re = " "
        noisio.red(self.nr)

    @property
    def callback(self):
        return self.callback

    @callback.setter
    def callback(self, function):
        noisio.irqcallback(function, self.nr)
        self._callbackfun = function

    @property
    def state(self):
        return noisio.get(self.nr)

class Nio(object):

    def __init__(self):
        pass


