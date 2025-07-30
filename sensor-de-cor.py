#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
#
# main.py — bip quando detectar vermelho no Color Sensor (porta S1)

from pybricks.hubs import EV3Brick
from pybricks.ev3devices import ColorSensor
from pybricks.parameters import Port, Color
from pybricks.tools import wait

# Inicializa
ev3    = EV3Brick()
sensor = ColorSensor(Port.S3)

# Loop principal
while True:
    if sensor.color() == Color.RED:
        ev3.speaker.beep()
    wait(100)
