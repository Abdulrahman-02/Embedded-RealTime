#include <Arduino.h>

void maTache(void * pvParameters){
  while(1){
    Serial.println("Hello Real Time World");
    delay(2000);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  xTaskCreate(maTache,"Ma tache",1024,NULL,1,NULL);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

