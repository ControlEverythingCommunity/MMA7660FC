// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MMA7660FC
// This code is designed to work with the MMA7660FC_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=MMA7660FC_I2CS#tabs-0-product_tabset-2

#include <Wire.h>
// MMA7660FC I2C address is 0x4C(76)
#define Addr 0x4C

void setup() 
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select mode register
  Wire.write(0x07);
  // Select active mode
  Wire.write(0x01);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select sample rate register register
  Wire.write(0x08);
  // 1 sample per second
  Wire.write(0x07);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[3];
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Data Register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
    
  // Request 3 bytes of data
  Wire.requestFrom(Addr, 3);
  
  // Read the three bytes 
  // xAccl, yAccl, zAccl
  if(Wire.available() == 3) 
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
  }  

  // Convert the data to 6-bits
  int xAccl = data[0] & 0x3F;
  if(xAccl > 31)
  {
    xAccl -= 64;
  }
  int yAccl = data[1] & 0x3F; 
  if(yAccl > 31)
  {
    yAccl -= 64;
  }
  int zAccl = data[2] & 0x3F;  
  if(zAccl > 31)
  {
    zAccl -= 64;
  }
    
  // Output data to serial monitor
  Serial.print("Acceleration in X-Axis :");
  Serial.println(xAccl);
  Serial.print("Acceleration in Y-Axis :");
  Serial.println(yAccl);
  Serial.print("Acceleration in Z-Axis :");
  Serial.println(zAccl) ;
  delay(500); 
}
