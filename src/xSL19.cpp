/*
	This is a library for the SL19 Infra Red Thermometer

	The board uses I2C for communication.
	
	The board communicates with two I2C devices:
	*	MLX90614
	
	Data Sheets:
	MLX90614	- https://www.melexis.com/-/media/files/documents/datasheets/mlx90614-datasheet-melexis.pdf
*/

#include "xSL19.h"

/*---Public Function---*/
/********************************************************
 	Constructor
*********************************************************/
xSL19::xSL19(void) 
{
	ambient_temp = 0;
	object_temp = 0;
	MLX90614_I2C_ADDR = 0x5A;
}

/********************************************************
 	Configure Sensor
*********************************************************/
bool xSL19::begin(void)
{
	return xCore.ping(MLX90614_I2C_ADDR);
}

/********************************************************
 	Reads Sensor Data
*********************************************************/
void xSL19::poll(void) 
{
	readAmbient();
	readObject();
}

/********************************************************
 	Get the Ambient Temperature from MLX90614 (C)
*********************************************************/
float xSL19::getAmbientTempC(void)
{
	return ambient_temp;
}

/********************************************************
 	Get the Ambient Temperature from MLX90614 (F)
*********************************************************/
float xSL19::getAmbientTempF(void)
{
	return ((ambient_temp * 1.8) + 32);	
}

/********************************************************
 	Get the Object Temperature from MLX90614 (C)
*********************************************************/
float xSL19::getObjectTempC(void)
{
	return object_temp;
}

/********************************************************
 	Get the Object Temperature from MLX90614 (F)
*********************************************************/
float xSL19::getObjectTempF(void)
{
	return ((object_temp * 1.8) + 32);
}

/*---Private Function---*/

/********************************************************
 	Read temperature Data from MLX90614
*********************************************************/
void xSL19::readAmbient(void) 
{
	float tempData; 
	tempData = readTemp(MLX90614_REG_TA);
	tempData *= .02;
  tempData -= 273.15;
	ambient_temp = tempData;
}

void xSL19::readObject(void) 
{
	float tempData;
	tempData = readTemp(MLX90614_REG_TOBJ1);
  tempData *= .02;
  tempData -= 273.15;
	object_temp = tempData;
}

uint16_t xSL19::readTemp(uint8_t reg)
{
  uint32_t data;
  data = read24(MLX90614_I2C_ADDR, reg);

	uint8_t HB,LB;
	HB = data >> 8;
	LB = data >> 16;

  return ((HB << 8)| LB);
}

uint32_t xSL19::read24(byte device, byte reg) {
	uint32_t value = 0;
	Wire.beginTransmission((uint8_t)device);
	Wire.write((uint8_t)reg);
	Wire.endTransmission(false);
	Wire.requestFrom((uint8_t)device, (uint8_t)3);
	if(Wire.available()){	
		value = Wire.read();
		value <<= 8;
		value |= Wire.read();
		value <<= 8;
		value |= Wire.read();
	}
	return value;
}
