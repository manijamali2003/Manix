'''
 In the name of God, the Compassionate, the Merciful
 Manix (c) 2021 Mani Jamali; Freedom at all
 Python based Manix kernel

 Example Python kernel
'''

from Manix import *

class Main (Kernel):

    def __init__(self):
        self.PrintLine("Manix kernel written in Python!")
        self.Generate()

if __name__ == '__main__':
    main = Main()