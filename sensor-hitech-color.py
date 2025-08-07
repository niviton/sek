#!/usr/bin/env pybricks-micropython
"""
main.py – Leitura do HiTechnic NXT Color Sensor V2
no EV3 com Pybricks sobre ev3dev, usando apenas
os modos RAW e COLOR para evitar Invalid argument.
"""

from pybricks.parameters import Port
from pybricks.iodevices import Ev3devSensor
from pybricks.tools import wait

# Nomes das cores conforme índice do sensor
COLOR_NAMES = {
    0:  'Nenhuma',    1:  'Preto',   2:  'Azul',    3:  'Verde',
    4:  'Amarelo',    5:  'Vermelho',6:  'Branco',  7:  'Marrom',
    8:  'Ciano',      9:  'Magenta',10: 'Laranja',11: 'Rosa',
    12: 'Cinza Claro',13: 'Cinza Escuro',14: 'Cor de Pele',
    15: 'Prata',      16: 'Ouro',   17: 'Outro'
}

def main():
    # Conecta o sensor à porta S4
    sensor = Ev3devSensor(Port.S4)

    print("Iniciando leitura do HiTechnic Color Sensor V2 (modos RAW e COLOR).")
    print("Pressione CTRL+C para parar.\n")

    try:
        while True:
            # 1) Leitura RAW → 3 valores (R, G, B)
            raw = sensor.read('RAW')
            r, g, b = raw[0], raw[1], raw[2]

            # 2) Leitura COLOR → 1 valor (índice da cor)
            color_id = sensor.read('COLOR')[0]
            color_name = COLOR_NAMES.get(color_id, 'Desconhecida')

            # 3) Exibe tudo em uma linha
            print(
                "ID cor={:2d} {:<12} | R={:3d} G={:3d} B={:3d}"
                .format(color_id, color_name, r, g, b)
            )

            # pequena pausa para não lotar o console
            wait(200)

    except KeyboardInterrupt:
        print("\nLeitura interrompida. Até a próxima!")

if __name__ == '__main__':
    main()
