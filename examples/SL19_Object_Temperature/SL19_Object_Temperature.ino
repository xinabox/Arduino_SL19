/*************************************************************
  This is an examples for the SL19
  Infra Red Thermometer

  You can buy one on our store!
  -----> https://xinabox.cc/products/SL19

  This example request an object temperature meausrement 
  to be made by the SL19 and display the data over 
  the Serial bus.

  Supported on the all ☒CHIPs

  The sensor communicates over the I2C Bus.

*************************************************************/

#include <xSL19.h>
#include <xCore.h>

xSL19 SL19;

// Variable to store the Print delat timer
unsigned long lastPrint;

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // Set the I2C Pins for CW01
#ifdef ESP8266
  Wire.pins(2, 14);
  Wire.setClockStretchLimit(15000);
#endif

  // Start the I2C Comunication
  Wire.begin();

  // Start the  SL19 Sensor
  SL19.begin();

  Serial.println("================================");
  Serial.println("    XINABOX SL19 Temperature    ");
  Serial.println("================================");

  //Delay for sensor to normalise
  delay(1000);  
}

void loop() {
  // Create a variable to store the data read from SW01
  float tempC;
  float tempF;
  tempC = tempF = 0;

  // Read and calculate data from SL19 sensor
  SL19.poll();

  if ((millis() - lastPrint) > 2000/*SERIAL_PRINT_DELAY*/) {
    // Request SL19 to get the temperature measurement and store in
    // the temperature variable
    tempC = SL19.getObjectTempC(); // Temperature in Celcuis
    tempF = SL19.getObjectTempF(); // Temperature in Farenheit

    // Display the recoreded data over the Serial Monitor
    Serial.print("Object Temp: ");
    Serial.print(tempC);
    Serial.println(" C");
    Serial.print("Object Temp: ");
    Serial.print(tempF);
    Serial.println(" F");

    Serial.println();

    lastPrint = millis();
  }
}
