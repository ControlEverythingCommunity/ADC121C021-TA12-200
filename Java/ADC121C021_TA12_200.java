// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADC121C021_TA12_200
// This code is designed to work with the ADC121C021_I2CS_TA12-200 I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class ADC121C021_TA12_200
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, ADC121C021_TA12_200 I2C address is 0x50(80)
		I2CDevice device = Bus.getDevice(0x50);

		// Select configuration register
		// Automatic conversion mode enabled
		device.write(0x02, (byte)0x20);
		Thread.sleep(500);

		// Read 2 bytes of data
		// raw_adc msb, raw_adc lsb
		byte[] data = new byte[2];
		device.read(data, 0, 2);

		// Convert the data to 12-bits
		int raw_adc = ((data[0] & 0x0F) * 256 + (data[1] & 0xFF));

		// Output data to screen
		System.out.printf("Digital value of analog input : %d %n", raw_adc);
	}
}
