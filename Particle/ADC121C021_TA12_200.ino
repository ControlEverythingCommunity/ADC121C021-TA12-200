// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADC121C021_TA12_200
// This code is designed to work with the ADC121C021_I2CS_TA12-200 I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// ADC121C021_TA12_200 I2C address is 0x50(80)
#define Addr 0x50

float current = 0.0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "ADC121C021");
  Particle.variable("current", current);

  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x02);
  // Automatic conversion mode enabled
  Wire.write(0x20);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[2];

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // current msb, current lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data to 12-bits
  current = (((data[0] & 0x0F) * 256) + data[1]) / 1000.0;

  // Output data to dashboard
  Particle.publish("Instantaneous Current value : ", String(current) + " A");
  delay(300);
}
