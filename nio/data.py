import xml.dom.minidom
from xml.dom.minidom import Node

doc = xml.dom.minidom.parse("pins.xml")

class Pindata(object):

    table = "+-----------+----+----+------------+"
 

    def __init__(self):
        pass

    @classmethod
    def pinout(cls):
        for board in doc.getElementsByTagName("board"):
            print cls.table
            for i,pin in enumerate(board.getElementsByTagName("pin")):
                for fct in pin.getElementsByTagName("function"):
                    for f in fct.childNodes:
                        if ((i%2)==0):
                            print "|{0:>10} | {1:>2} | {2:>2} |".format(f.data, i+1, i+2),
                        else:
                            print "{0:>10} |".format(f.data)
                            print cls.table

    
