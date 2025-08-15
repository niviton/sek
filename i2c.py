#!/usr/bin/env pybricks-micropython
from pybricks.hubs import EV3Brick
from pybricks.parameters import Port
from pybricks.iodevices import I2CDevice

ev3 = EV3Brick()
arduino = I2CDevice(Port.S1, 0x08)

ev3.speaker.beep()
ev3.screen.print("Enviando 123")
# envia o valor 123
arduino.write(123)
