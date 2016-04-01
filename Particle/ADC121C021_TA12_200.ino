// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADC121C021_TA12_200
// This code is designed to work with the ADC121C021_I2CS_TA12-200 I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// ADC121C021_TA12_200 I2C address is 0x50(80)
#define Addr 0x50

int raw_adc = 0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "ADC121C021");
  Particle.variable("rawADC", raw_adc);
    
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop() 
{
  unsigned int data[2];
  
  // Start I2C transmission
  Wire.beginTransmission(Addr); 
  // Calling conversion result register, 0x00(0)
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();
  
  // Request 2 bytes
  Wire.requestFrom(Addr, 2);
  
  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if(Wire.available() == 2)
  {  
      data[0] = Wire.read();
      data[1] = Wire.read();
  }
  delay(300);
    
  // Convert the data to 12 bits
  raw_adc = ((data[0] * 256) + data[1]) & 0x0FFF;

  // Output data to dashboard
  Particle.publish("Digital value of analog input: ", String(raw_adc));

}
