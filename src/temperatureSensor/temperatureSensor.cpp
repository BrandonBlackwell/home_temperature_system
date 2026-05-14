#include <cmath>
#include <iostream>

#include "temperatureSensor.hpp"

float TemperatureSensor::getTemperatureCelsius(float rawADC){
  float temperature = calculateTemperature(rawADC);
  if (std::isnan(temperature)) {
    return NAN;
  }
  return temperature - 273.15f; // Convert from Kelvin to Celsius
}

float TemperatureSensor::getTemperatureFahrenheit(float rawADC){
  float temperature = calculateTemperature(rawADC);
    if (std::isnan(temperature)) {
    return NAN;
  }
  return (temperature - 273.15f) * 9/5 + 32.0f; // Convert from Kelvin to Fahrenheit
}

float TemperatureSensor::calculateTemperature(float rawADC) {
  rawADC = validateAnalogValue(rawADC);
  if (std::isnan(rawADC)) {
    return NAN; // Return NaN if the input is invalid
  }
  // Get resistance using voltage divider: R = R_fixed * (Vin / Vout - 1)
  float resistance = this->resistorValue * (this->vin / rawADC - 1.0f);
  // Convert resistance to temperature using Beta parameter equation: T = 1 / (1/T0 + 1/B * ln(R/R0))
  float temperature = 1 / (1/this->temp25CtoK + 1/this->betaValue * log(resistance / this->resistorValue));
  return temperature;
}

float TemperatureSensor::validateAnalogValue(float rawADC) {
  if (rawADC < 1.0 || rawADC >= 4095.0) {
    std::cerr << "Invalid raw ADC value: " << rawADC << ". Must be between 1 and 4094." << std::endl;
    return NAN; // Avoid division by zero or negative resistance
  }
  return rawADC;
}
