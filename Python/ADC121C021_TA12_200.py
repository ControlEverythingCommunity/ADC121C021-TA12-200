# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# ADC121C021_TA12_200
# This code is designed to work with the ADC121C021_I2CS_TA12-200 I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# ADC121C021_TA12_200 address, 0x50(80)
# Select configuration register, 0x02(02)
#		0x20(32)	Automatic conversion mode enabled
bus.write_byte_data(0x50, 0x02, 0x20)

time.sleep(0.5)

# ADC121C021_TA12_200 address, 0x50(80)
# Read data back from 0x00(00), 2 bytes
# raw_adc MSB, raw_adc LSB
data = bus.read_i2c_block_data(0x50, 0x00, 2)

# Convert the data to 12-bits
raw_adc = ((data[0] & 0x0F) * 256) + data[1]

# Output data to screen
print "Digital value of analog input : %d" %raw_adc
