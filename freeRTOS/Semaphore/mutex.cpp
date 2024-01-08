#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t ecranMutex;

void imprime(char *message) {
    int index = 0;
    char car;
    do {
        car = message[index];
        index++;
        printf("%c", car);
        for (int i = 0; i < 0xFFFF; i++);
    } while (car != '\0');
}

void maTache(void *params) {
    char *message = "Salut, comment ca va? \n";
    while (true) {
        // p(s)
        xSemaphoreTake(ecranMutex, portMAX_DELAY);
        imprime(message);
        // v(s)
        xSemaphoreGive(ecranMutex);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void myTask(void *params) {
    char *message = "Hello, how are you? \n";
    while (true) {
        // p(s)
        xSemaphoreTake(ecranMutex, portMAX_DELAY);
        imprime(message);
        // v(s)
        xSemaphoreGive(ecranMutex);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void) {
    ecranMutex = xSemaphoreCreateMutex();
    xTaskCreate(maTache, "maTache", 4096, NULL, 4, NULL);
    xTaskCreate(myTask, "maTache", 4096, NULL, 4, NULL);
}
