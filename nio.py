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

    @classmethod
    def pins(cls):
        for i in cls.instances:
            print i

    def __repr__(self):

        message = """
                      Pin Object Status:\n
                      Pin Nr: {0}\n
                      Pin communication: {1}\n
                      Pin sate: {2}\n
                      Pin PUD: {3}\n
                      Pin Schmidt: {4}\n
                      Pin Alternate functions: {5}\n
                      Pin interrupt: {6}\n
                      Pin callback functions: {7}\n
                   """
        return message.format(self.nr, self._io, self._state, self._pud,"NIY","NIY","NIY","NIY")

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
        noisio.pullup(self.nr)

    @property
    def pulldown(self):
        noisio.pulldown(self.nr)

    @property
    def state(self):
        return noisio.get(self.nr)

class Nio(object):

    def __init__(self):
        pass


