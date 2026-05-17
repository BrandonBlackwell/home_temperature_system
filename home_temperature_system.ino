/*
This code reads the temperature from a thermistor connected to an Arduino Nano. 
The thermistor is part of a voltage divider circuit, and the code calculates 
the resistance of the thermistor based on the voltage reading from the ADC. 
Then, it uses the Beta parameter equation to calculate the temperature in Kelvin, 
which is then converted to Celsius and Fahrenheit. The temperature, in Celsius, is
used to determine the temperature zone which correlates to a zone distribution. 
This zone distribution dictates the color of the RGB LED.

TODO:
- Add HAL: Hardware abstraction layer
- Add JSON task
- Add logging task
 */
#include <cmath>

#include "src/temperatureSensor/temperatureSensor.hpp"
#include "src/rgbController/rgbController.hpp"

const int BETA_VALUE = 3950;
const int RESISTOR_10K = 10000; // 10k ohms
const int Vin = 4095; // 3.3V represented in ADC units (12-bit ADC)
const float TEMP_25C_to_K = 298.15; // 25C to K. Formula: 25 + 273.15K
const uint8_t RED_LED = 9;
const uint8_t GREEN_LED = 10;
const uint8_t BLUE_LED = 11;

struct TempTaskParams {
    TemperatureSensor *sensor;
    QueueHandle_t tempQueue;
};

struct RGBTaskParams {
    RGBController *rgb_controller;
    QueueHandle_t tempQueue;
};

void setup() {
  Serial.begin(9600);
  TemperatureSensor *tempSensor = new TemperatureSensor(
          BETA_VALUE, 
          RESISTOR_10K, 
          Vin, 
          TEMP_25C_to_K
  );
  float temps[2]; // temps[0] for Celsius, temps[1] for Fahrenheit
  QueueHandle_t tempQueue = xQueueCreate( 50, sizeof( temps ) );
  if (tempQueue == NULL) {
    Serial.println("Failed to create temperature queue");
  }

  TempTaskParams *tempTaskParams = new TempTaskParams();
  tempTaskParams->sensor = tempSensor;
  tempTaskParams->tempQueue = tempQueue;

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  RGBController *rgb_controller = new RGBController(
                                    RED_LED,
                                    GREEN_LED,
                                    BLUE_LED
                                 );

  RGBTaskParams *rgbTaskParams = new RGBTaskParams();
  rgbTaskParams->rgb_controller = rgb_controller;
  rgbTaskParams->tempQueue = tempQueue;

  // TODO: Ensure STACK_SIZE is sufficient for the task's needs
  BaseType_t tempTaskCreation = xTaskCreate(temperatureTask, "Temperature Task", 10000, tempTaskParams, 1, NULL);
  BaseType_t rgbTaskCreation = xTaskCreate(rgbTask, "RGB Task", 10000, rgbTaskParams, 1, NULL);
  if (tempTaskCreation != pdPASS) {
    Serial.println("Failed to create Temperature Task");
  }
  if (rgbTaskCreation != pdPASS) {
    Serial.println("Failed to create RGB Task");
  }
}

void loop() {}

void temperatureTask( void *pvParameters )
{
  TempTaskParams *params = (TempTaskParams *) pvParameters;
  TemperatureSensor *tempSensor = params->sensor;
  QueueHandle_t tempQueue = params->tempQueue;

  for( ;; )
  {
    int sensorValue = analogRead(A0);
    
    float temps[2];
    temps[0] = tempSensor->getTemperatureCelsius(sensorValue);
    temps[1] = tempSensor->getTemperatureFahrenheit(sensorValue);

    if (tempQueue != NULL) {
      if (xQueueSend( tempQueue, (void *) &temps, ( TickType_t ) 20 ) != pdPASS) // Handle queue send failure
      {
        /* Failed to post the message, even after 20 ticks. */
        Serial.println("Failed to send temperature data to queue");
      }
      vTaskDelay(pdMS_TO_TICKS(2000));
    } 
  }
}

void rgbTask(void *pvParameters) {
  // TODO: Blink LED every two seconds
  float tempReadings[2];
  RGBTaskParams *rgbTaskParamsPtr = (RGBTaskParams *) pvParameters;
  RGBController *rgb_controller = rgbTaskParamsPtr->rgb_controller;
  QueueHandle_t tempQ = rgbTaskParamsPtr->tempQueue;

  for( ;; )
  { 
    if(xQueueReceive(tempQ, &( tempReadings ), ( TickType_t ) 10 ) == pdPASS) {
      float tempCelsius = tempReadings[0];
      float tempFahrenheit = tempReadings[1];

      Serial.print("Temperature: ");
      Serial.print(tempCelsius);
      Serial.print(" °C, ");
      Serial.print(tempFahrenheit);
      Serial.println(" °F");

      // Update RGB LED color based on temperature
      rgb_controller->setColor(tempCelsius);

      analogWrite(rgb_controller->red_pin, rgb_controller->red);
      analogWrite(rgb_controller->green_pin, rgb_controller->green);
      analogWrite(rgb_controller->blue_pin, rgb_controller->blue);

      vTaskDelay(pdMS_TO_TICKS(1000)); // Short delay to allow other tasks to run
    }
  } 
}
