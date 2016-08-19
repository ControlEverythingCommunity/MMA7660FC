# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# MMA7660FC
# This code is designed to work with the MMA7660FC_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Accelorometer?sku=MMA7660FC_I2CS#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# MMA7660FC address, 0x4C(76)
# Select mode register, 0x07(07)
#		0x01(01)	Active mode
i2c.writeByte(0x4C, 0x07, 0x01)
# MMA7660FC address, 0x4C(76)
# Select sample rate register, 0x08(08)
#		0x07(07)	1 Sample/second active
i2c.writeByte(0x4C, 0x08, 0x07)

time.sleep(0.5)

# MMA7660FC address, 0x4C
# Read data back from 0x00, 3 bytes
# X-Axis Accl, Y-Axis Accl, Z-Axis Accl
data = i2c.readBytes(0x4C, 0x00, 3)

# Convert the data to 6-bits
xAccl = data[0] & 0x3F
if xAccl > 31 :
	xAccl -= 64

yAccl = data[1] & 0x3F
if yAccl > 31 :
	yAccl -= 64

zAccl = data[2] & 0x3F
if zAccl > 31 :
	zAccl -= 64

# Output data to screen
print "Acceleration in X-Axis : %d" %xAccl
print "Acceleration in Y-Axis : %d" %yAccl
print "Acceleration in Z-Axis : %d" %zAccl
