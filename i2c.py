#!/usr/bin/env pybricks-micropython
from pybricks.hubs import EV3Brick
from pybricks.parameters import Port
from pybricks.iodevices import I2CDevice
import time

ev3 = EV3Brick()
arduino = I2CDevice(Port.S1, 0x08)

ev3.speaker.beep()
ev3.screen.print("Teste I2C simplificado")

while True:
    # --- Comando LED ON ---
    arduino.write(1)  # 1 = LED ON
    print("EV3 -> LED ON")
    time.sleep(1)

    # --- Comando LED OFF ---
    arduino.write(0)  # 0 = LED OFF
    print("EV3 -> LED OFF")
    time.sleep(1)

    # --- Pedido de sensor fictício ---
    arduino.write(2)        # 2 = pede valor do sensor
    time.sleep(0.05)        # pequena pausa antes de ler
    sensor = arduino.read(1)  # lê 1 byte do Arduino
    if sensor:
        print("EV3 <- sensor fictício:", sensor[0])
    time.sleep(1)
