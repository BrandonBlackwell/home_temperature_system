#include <math.h>
/*
This code reads the temperature from a thermistor connected to an Arduino Nano. 
The thermistor is part of a voltage divider circuit, and the code calculates 
the resistance of the thermistor based on the voltage reading from the ADC. 
Then, it uses the Beta parameter equation to calculate the temperature in Kelvin, 
which is then converted to Celsius and Fahrenheit.

TODO: Create temperature object
 */
const int BETA_VALUE = 3950;
const int RES = 10000; // 10k ohms
const float Vin = 1023; // Nano has 10-bit ADC. So, max value 2^10-1 or 1023
const float TEMP_KNOWN = 298.15; // 25C to K. Formula: 25 + 273.15K
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  delay(2000); 
  int sensorValue = analogRead(A0);
  // Voltage divider: R = R_fixed * (Vin / Vout - 1)
  float resistance = RES * (Vin / sensorValue - 1);

  // Compute Temp
  float temp = 1 / (1/TEMP_KNOWN + 1/BETA_VALUE * log(resistance / RES));

  // Convert to Celsius
  float celsius = temp - 273.15;
  // Convert to Fahrenheit
  float fahrenheit = (celsius * 9 / 5) + 32;


  Serial.println("Temperature Celsius: ");
  Serial.println(celsius);

  Serial.println("Temperature Fahrenheit: ");
  Serial.println(fahrenheit);

}
