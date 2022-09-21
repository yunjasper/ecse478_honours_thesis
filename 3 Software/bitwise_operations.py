"""
experimentation with bitwise operations in python.

author: jasper
date created: 2022-09-07
"""

# byte array with sample start of frame info
frame_header = bytearray([0b00100110, 0b00000011])

byte1 = frame_header[0]
dlc = frame_header[1]

# isolate mode bit (should be 0)
print((byte1 & (0x1 << 6)) >> 6)

# isolate RTR bit (should be 1)
print((byte1 & (0x1 << 5)) >> 5)