/*
This code reads the temperature from a thermistor connected to an Arduino Nano. 
The thermistor is part of a voltage divider circuit, and the code calculates 
the resistance of the thermistor based on the voltage reading from the ADC. 
Then, it uses the Beta parameter equation to calculate the temperature in Kelvin, 
which is then converted to Celsius and Fahrenheit.

TODO:
- Convert loop code to task-based structure for better performance and responsiveness. 
 */
#include <cmath>

#include "src/temperatureSensor/temperatureSensor.hpp"

const int BETA_VALUE = 3950;
const int RESISTOR_10K = 10000; // 10k ohms
const int Vin = 4095; // 3.3V represented in ADC units (12-bit ADC)
const float TEMP_25C_to_K = 298.15; // 25C to K. Formula: 25 + 273.15K
const int RED_LED = 9;
const int GREEN_LED = 10;
const int BLUE_LED = 11;

struct TempTaskParams {
    TemperatureSensor *sensor;
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

  // TODO: Ensure STACK_SIZE is sufficient for the task's needs
  BaseType_t tempTaskCreation = xTaskCreate(temperatureTask, "Temperature Task", 10000, tempTaskParams, 1, NULL);
  BaseType_t rgbTaskCreation = xTaskCreate(rgbTask, "RGB Task", 10000, tempQueue, 1, NULL);
  if (tempTaskCreation != pdPASS) {
    Serial.println("Failed to create Temperature Task");
  }
  if (rgbTaskCreation != pdPASS) {
    Serial.println("Failed to create RGB Task");
  }
}

void loop() { 
  // int sensorValue = analogRead(A0);
  // TemperatureSensor tempSensor = TemperatureSensor(
  //   BETA_VALUE, 
  //   RESISTOR_10K, 
  //   Vin, 
  //   TEMP_25C_to_K
  // );

  // float tempCelsius = tempSensor.getTemperatureCelsius(sensorValue);
  // float tempFahrenheit = tempSensor.getTemperatureFahrenheit(sensorValue);

  // Serial.print("Temperature: ");
  // Serial.print(tempCelsius);
  // Serial.print(" °C, ");
  // Serial.print(tempFahrenheit);
  // Serial.println(" °F");
  // delay(2000); // Delay for 2 seconds before the next reading
}

void temperatureTask( void *pvParameters )
{
  TempTaskParams *params = (TempTaskParams *) pvParameters;
  TemperatureSensor *tempSensor = params->sensor;
  QueueHandle_t tempQueue = params->tempQueue;

  for( ;; )
  {
      // Task code goes here. This is an infinite loop, so the task will run indefinitely.
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

    /* Tasks must not attempt to return from their implementing
       function or otherwise exit. In newer FreeRTOS port
       attempting to do so will result in an configASSERT() being
       called if it is defined. If it is necessary for a task to
       exit then have the task call vTaskDelete( NULL ) to ensure
       its exit is clean. */
}

void rgbTask(void *pvParameters) {
  float tempReadings[2];
  QueueHandle_t tempQueue = (QueueHandle_t)pvParameters;

  for( ;; )
  {
    /* Pseudo code showing a task waiting for an event
        with a block time. If the event occurs, process it.
        If the timeout expires before the event occurs, then
        the system may be in an error state, so handle the
        error. Here the pseudo code "WaitForEvent()" could
        replaced with xQueueReceive(), ulTaskNotifyTake(),
        xEventGroupWaitBits(), or any of the other FreeRTOS
        communication and synchronisation primitives. 
    */
    
    if(xQueueReceive(tempQueue, &( tempReadings ), ( TickType_t ) 10 ) == pdPASS) {
      float tempCelsius = tempReadings[0];
      float tempFahrenheit = tempReadings[1];
      // Process the temperature readings (e.g., update RGB LED color based on temperature)
      Serial.print("Temperature: ");
      Serial.print(tempCelsius);
      Serial.print(" °C, ");
      Serial.print(tempFahrenheit);
      Serial.println(" °F");
      // TODO: Add code to update RGB LED color based on temperature thresholds
      int comfortable = 23;
      int hot = 26;
      if (tempCelsius < comfortable) {
        // Too cold - set LED to blue
        digitalWrite(BLUE_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, LOW);
      }
      if (tempCelsius >= hot) {
          // Too hot - set LED to red
          digitalWrite(RED_LED, HIGH);
          digitalWrite(GREEN_LED, LOW);
          digitalWrite(BLUE_LED, LOW);
      }
      vTaskDelay(pdMS_TO_TICKS(1000)); // Short delay to allow other tasks to run
    }
  } 
}

// void jsonTask(){}
// void logTask(){}
