// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADC121C021_TA12_200
// This code is designed to work with the ADC121C021_I2CS_TA12-200 I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

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
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, ADC121C021_TA12_200 I2C address is 0x50(80)
	ioctl(file, I2C_SLAVE, 0x50);

	// Select configuration register(0x02)
	// Automatic conversion mode enabled(0x20)
	char config[2] = {0};
	config[0]= 0x02;
	config[1]= 0x20;
	write(file, config, 2);
	sleep(1);

	// Read 2 bytes of data from register(0x00)
	// current msb, current lsb
	char reg[1] = {0x00};
	write(file, reg, 1);
	char data[2] = {0};
	if(read(file, data, 2) != 2)
	{
		printf("Erorr : Input/output Erorr \n");
	}
	else
	{
		// Convert the data to 12-bits
		double current = ((data[0] & 0x0F) * 256 + data[1]) / 1000.0;

		// Output data to screen
		printf("Instantaneous Current value : %.2f \n", current);
	}
}
