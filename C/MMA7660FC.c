// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MMA7660FC
// This code is designed to work with the MMA7660FC_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=MMA7660FC_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, MMA7660FC I2C address is 0x4C(76)
	ioctl(file, I2C_SLAVE, 0x4C);

	// Select sample rate register(0x08)
	// 1 Sample/second(0x07)
	char config[2] = {0};
	config[0] = 0x08;
	config[1] = 0x07;
	write(file, config, 2);

	// Select mode register(0x07)
	// Active mode(0x01)
	config[0] = 0x07;
	config[1] = 0x01;
	write(file, config, 2);
	sleep(1);

	// Read 3 bytes of data
	// xAccl, yAccl, zAccl
	char reg[1] = {0x00};
	write(file, reg, 1);
	char data[3] = {0};
	if(read(file, data, 3) != 3)
	{
		printf("Error : Input/output Error \n");
	}
	else
	{
		// Convert the data to 6-bits
		int xAccl = data[0] & 0x3F;
		if(xAccl > 31)
		{
			xAccl -= 64;
		}

		int yAccl = data[1] & 0x3F;;
		if(yAccl > 31)
		{
			yAccl -= 64;
		}

		int zAccl = data[2] & 0x3F;;
		if(zAccl > 31)
		{
			zAccl -= 64;
		}

		// Output data to screen
		printf("Acceleration in X-Axis : %d \n", xAccl);
		printf("Acceleration in Y-Axis : %d \n", yAccl);
		printf("Acceleration in Z-Axis : %d \n", zAccl);
	}
}
