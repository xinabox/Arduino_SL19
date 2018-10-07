/*
	This is a library for the SL19 Infra Red Thermometer

	The board uses I2C for communication.
	
	The board communicates with two I2C devices:
	*	MLX90614
	
	Data Sheets:
	MLX90614	- https://www.melexis.com/-/media/files/documents/datasheets/mlx90614-datasheet-melexis.pdf
*/

#ifndef Arduino_SL19_h
#define Arduino_SL19_h

// Include File Headers
#include "xCore.h"

// MLX90614 Register Descriptions
#define MLX90614_REG_RAWIR1 0x04
#define MLX90614_REG_RAWIR2 0x05
#define MLX90614_REG_TA 		0x06
#define MLX90614_REG_TOBJ1 	0x07
#define MLX90614_REG_TOBJ2 	0x08
#define MLX90614_REG_TOMAX 	0x20
#define MLX90614_REG_TOMIN 	0x21
#define MLX90614_REG_PWMCTRL 0x22
#define MLX90614_REG_TARANGE 0x23
#define MLX90614_REG_EMISS 	0x24
#define MLX90614_REG_CONFIG 0x25
#define MLX90614_REG_ADDR 	0x0E
#define MLX90614_REG_ID1 	0x3C
#define MLX90614_REG_ID2 	0x3D
#define MLX90614_REG_ID3 	0x3E
#define MLX90614_REG_ID4 	0x3F

class xSL19: public xCoreClass
{
	public:
		/**
		* Constructor
		* Creates a new instance of Sensor class.
		*/	
		xSL19();

		/*
		* Runs the setup of the sensor. 
		* Call this in setup(), before reading any sensor data.
		*
		* @return true if setup was successful.
		*/		
		bool 	begin(void);
		
		/*
		* Used read all raw sensors data and convert to usefull results. 
		* Call this in loop(). 
		*
		* @return none
		*/		
		void 	poll(void);
		
		/*
		* Used to get Ambient Temperature.
		* Call this in loop(). 
		*
		* @return tempC. Returns float value of ambient temperature.
		*/		
		float 	getAmbientTempC(void);

		/*
		* Used to get Ambient Temperature.
		* Call this in loop(). 
		*
		* @return tempF. Returns float value of ambient temperature.
		*/			
		float	getAmbientTempF(void);
		
		/*
		* Used to get the Object Temperature.
		* Call this in loop(). 
		*
		* @return tempF. Returns float value of object temperature.
		*/		
		float 	getObjectTempC(void);

		/*
		* Used to get the Object Temperature.
		* Call this in loop(). 
		*
		* @return tempF. Returns float value of object temperature.
		*/			
		float	getObjectTempF(void);

	private:
		/*
		* Reads RAW temperature data.
		*
		* @return none
		*/		
		void 	readAmbient(void);
		void	readObject(void);
		uint16_t readTemp(uint8_t reg);

		// Used to store device I2C Address
		uint8_t 	MLX90614_I2C_ADDR;

		// Used to store temperature Data
		float 		ambient_temp;
		float 		object_temp;
};

#endif
