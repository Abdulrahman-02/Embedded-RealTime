#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/timers.h>
#include <stdio.h>
#include <freertos/event_groups.h>


#define BTN1_PIN 22
#define BTN2_PIN 23

EventGroupHandle_t butoonEventGroup;

#define BTN1_BIT (1 << 0)
#define BTN2_BIT (1 << 1)

void BTN1_Task(void *params) {
    while (true) {
        if(xEventGroupWaitBits(butoonEventGroup, BTN1_BIT, pdTRUE, pdFalse, portMAX_DELAY)) {
            printf("BTN1 pressed\n");
        }
    }
}

void BTN2_Task(void *params) {
    while (true) {
        if(xEventGroupWaitBits(butoonEventGroup, BTN2_BIT, pdTRUE, pdFalse, portMAX_DELAY)) {
            printf("BTN2 pressed\n");
        }
    }
}


void BTN_SIM_Task(void *params) {
    while (true) {
        if(xEventGroupWaitBits(butoonEventGroup, (BTN1_BIT | BTN2_BIT), pdTRUE, pdFalse, portMAX_DELAY)) {
            printf("BTN1 and BTN2 pressed\n");
        }
    }
}

void buttonTimerCallback(TimerHandle_t xTimer) {
    xEventGroupSetBits(buttonEventGroup, BTN1_BIT);
    vTaskDelay(pdMS_TO_TICKS(50));
    xEventGroupSetBits(buttonEventGroup, BTN2_BIT);
}

void app_main() {
    butoonEventGroup = xEventGroupCreate();
    
    xTaskCreate(&BTN1_Task, "BTN1_Task", 2048, NULL, 4, NULL);
    xTaskCreate(&BTN2_Task, "BTN2_Task", 2048, NULL, 4, NULL);
    xTaskCreate(&BTN_SIM_Task, "BTN_SIM_Task", 2048, NULL, 4, NULL);

    TimerHandle_t buttonTimer = xTimerCreate("buttonTimer", pdMS_TO_TICKS(1000), pdTRUE, NULL, buttonTimerCallback);
    xTimerStart(buttonTimer, 0);
}