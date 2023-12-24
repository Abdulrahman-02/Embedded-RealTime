#include <Arduino.h>

void TacheOne(void * pvParameters){
    while(1){
        Serial.println("Hello from task 1");
        delay(2000);
    }
}

void TacheTwo(void * pvParameters){
    while(1){
        Serial.println("Hello from task 2");
        delay(2000);
    }
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    xTaskCreate(TacheOne,"Task 1",1024,NULL,1,NULL);
    xTaskCreate(TacheTwo,"Task 2",1024,NULL,1,NULL);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}