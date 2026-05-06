class TemperatureSensor
{
private:
  const int betaValue;
  const int resistorValue;
  const float vin;
  const float temp25CtoK;
public:
  TemperatureSensor(
    const int betaValue, 
    const int resistorValue, 
    const float vin, 
    const float temp25CtoK
  ) : 
  betaValue(betaValue), 
  resistorValue(resistorValue), 
  vin(vin), 
  temp25CtoK(temp25CtoK) 
  {}
  
  ~TemperatureSensor() = default;

  float getTemperatureCelsius(int sensorValue);
  float getTemperatureFahrenheit(int sensorValue);
};