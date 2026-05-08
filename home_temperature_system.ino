/*
This code reads the temperature from a thermistor connected to an Arduino Nano. 
The thermistor is part of a voltage divider circuit, and the code calculates 
the resistance of the thermistor based on the voltage reading from the ADC. 
Then, it uses the Beta parameter equation to calculate the temperature in Kelvin, 
which is then converted to Celsius and Fahrenheit.
 */
#include <cmath>

#include "src/temperatureSensor.hpp"

const int BETA_VALUE = 3950;
const int RESISTOR_10K = 10000; // 10k ohms
const int Vin = 4095; // 3.3V represented in ADC units (12-bit ADC)
const float TEMP_25C_to_K = 298.15; // 25C to K. Formula: 25 + 273.15K
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() { 
  int sensorValue = analogRead(A0);
  TemperatureSensor tempSensor = TemperatureSensor(
    BETA_VALUE, 
    RESISTOR_10K, 
    Vin, 
    TEMP_25C_to_K
  );

  float tempCelsius = tempSensor.getTemperatureCelsius(sensorValue);
  float tempFahrenheit = tempSensor.getTemperatureFahrenheit(sensorValue);

  Serial.print("Temperature: ");
  Serial.print(tempCelsius);
  Serial.print(" °C, ");
  Serial.print(tempFahrenheit);
  Serial.println(" °F");
  delay(2000); // Delay for 2 seconds before the next reading
}
