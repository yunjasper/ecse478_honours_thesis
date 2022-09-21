"""
tests serial com port shenanigans in Python with an embedded device (e.g. Arduino/Teensy/STM32).

author: jasper 
date created: 2022-09-06
"""
import struct
import serial


port = "COM21"

if __name__ == '__main__':
    try:
        ser = serial.Serial(port, 9600, timeout=3)
        ser.close()
        ser.open()

        while True:
            read_val = ser.read(8)

            read_val = bytearray([0, 1, 2, 3, 87, 183, 161, 195])

            print('i = ' + str(read_val[0]))
            print('j = ' + str(read_val[1]))
            print('k = ' + str(read_val[2]))
            print('m = ' + str(read_val[3]))

            # print('f = ' + str(bin_to_float_ieee754(read_val[4:])))
            f = struct.unpack('@f', read_val[4:])
            print('f = ' + str(f[0]))

            break
            
    except serial.SerialException:
        print('error occurred :(')

