from microbit import *

class Motor(object):
    def __init__(self, vref_, in1_, in2_):
        self.vref = vref_
        self.in1 = in1_
        self.in2 = in2_
    def start_forward(self, speed=500):
        self.vref.write_analog(speed)
        self.in1.write_digital(1)
        self.in2.write_digital(0)
    def start_backward(self, speed=500):
        self.vref.write_analog(speed)
        self.in1.write_digital(0)
        self.in2.write_digital(1)
    def stop(self):
        self.in1.write_digital(1)
        self.in2.write_digital(1)
    def brake(self, delay=1000):
        self.in1.write_digital(1)
        self.in2.write_digital(1)
