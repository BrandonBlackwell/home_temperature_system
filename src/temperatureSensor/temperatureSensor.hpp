class TemperatureSensor
{
private:
  const float betaValue;
  const float resistorValue;
  const float vin;
  const float temp25CtoK;
public:
  TemperatureSensor(
    const float betaValue, 
    const float resistorValue, 
    const float vin, 
    const float temp25CtoK
  ) : 
    betaValue(betaValue), 
    resistorValue(resistorValue), 
    vin(vin), 
    temp25CtoK(temp25CtoK) 
  {}
  
  ~TemperatureSensor() = default;

  float getTemperatureCelsius(float rawADC);
  float getTemperatureFahrenheit(float rawADC);

private:
  float calculateTemperature(float rawADC);
  float validateAnalogValue(float rawADC);
};