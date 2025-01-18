/*
  Tiny BME280 Library
  https://github.com/technoblogy/tiny-bme280
  Example to print out environmental data (temperature, pressure, humidity) once per second.

  Created by Max Kendall
  Modified 20 January 2024
  Library by Technoblogy

  Connections:
  BME --- MCU
  VCC to 5v
  GND to GND
  SDA to A4
  SCL to A5

  Set your Serial monitor to 9600 baud and click the magnifiying glass icon on the top-right.
*/

#include <TinyBME280.h>

void setup() {
  // Runs once at start or board reset

  // Uncomment to change address. Default is 0x77
  BME280setI2Caddress(0x76);

  // Begin the I2C connection with BME280
  BME280setup();

  // Begin Serial monitor output for debugging
  Serial.begin(9600);

  Serial.println("BME280 Interface Example.");
}

void loop() {
  // Runs forever after setup

  // Gives the temperature as a signed 32-bit integer in °C with a resolution of 0.01°C. So an output value of “5123” equals 51.23°C.
  float temp = BME280temperature() / 100;

  // Pives the pressure in Pa as an unsigned 32-bit integer, so an output value of “96386” equals 96386 Pa, or 963.86 hPa.
  float press = BME280pressure() / 100;

  // Gives the humidity in %RH with a resolution of 0.01% RH, so an output value of “4653” represents 46.53 %RH.
  float humid = BME280humidity() / 100;


  // Print the data to Serial output!
  Serial.print("Temperature: ");
  Serial.print(temp);

  Serial.print(", Pressure: ");
  Serial.print(press);

  Serial.print(", Humidity: ");
  Serial.println(humid);

  delay(100);
}

/////////////////////////////////////////////////////////////
/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created  24 Nov 2010
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "Hello, World!";

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}