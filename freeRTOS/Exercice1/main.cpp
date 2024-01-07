#include <Arduino.h>

void tacheHello(void * pvParameters) {
  while(1) {
    Serial.println("Hello freeRTOS");
    delay(2000)
  }
}

void setup() {
  // run once 
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  xTaskCreate(tacheHello,"Hello",1024,NULL,1,NULL);
}

void loop() {
  // main code
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
