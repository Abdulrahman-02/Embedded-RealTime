#include <Arduino.h>

TaskHandle_t TaskBlueLEDHandle;
TaskHandle_t TaskRedLEDHandle;

const int blueLED = 23;
const int redLED = 22;

void TaskBlueLED(void *pvParameters) {
pinMode(blueLED, OUTPUT);

while(1) {
    digitalWrite(blueLED, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS); // On for 0.5 seconds
    digitalWrite(blueLED, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS); // Off for 0.5 seconds	
	}
}

void TaskRedLED(void *pvParameters) {
  pinMode(redLED, OUTPUT);

  while (1) {
    digitalWrite(redLED, HIGH);
    vTaskDelay(250 / portTICK_PERIOD_MS); // On for 0.25 seconds
    digitalWrite(redLED, LOW);
    vTaskDelay(250 / portTICK_PERIOD_MS); // Off for 0.25 seconds
  }
}

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(TaskBlueLED, "TaskBlueLED", 1024, NULL, 1, &TaskBlueLEDHandle, 0);
  xTaskCreatePinnedToCore(TaskRedLED, "TaskRedLED", 1024, NULL, 1, &TaskRedLEDHandle, 1);
}

void loop() {
// not used
}
