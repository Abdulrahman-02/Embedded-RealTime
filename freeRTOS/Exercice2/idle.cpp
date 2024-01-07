#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"


int idleCountForCpu0 =0;
int idleCountForCpu1 =0;


bool incrIdleForCpu0(void){
    idleCountForCpu0 ++;
    return false;
}

bool incrIdleForCpu1(void){
    idleCountForCpu1 ++;
    return false;
}

void afficheIdleCoucnt(void* pvPar){
    while(true){
        printf("Idle Time du CPU0 = %d\n",idleCountForCpu0);
        printf("Idle Time du CPU1 = %d\n",idleCountForCpu1);
        idleCountForCpu0 = 0;
        idleCountForCpu1 = 0;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void tache(void* pvParams){
    while(true){
        for(int i = 0; i<500000; i++);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}d


void app_main(void)
{
  esp_register_freertos_idle_hook_for_cpu(incrIdleForCpu0,0);
  esp_register_freertos_idle_hook_for_cpu(incrIdleForCpu1,1);
  xTaskCreate(tache, "T1",6000,NULL,3,NULL);
  xTaskCreate(tache, "T2",6000,NULL,3,NULL);
  xTaskCreate(tache, "T3",6000,NULL,3,NULL);
  xTaskCreate(tache, "T4",6000,NULL,3,NULL);
  xTaskCreate(tache, "T5",6000,NULL,3,NULL);
  xTaskCreate(tache, "T6",6000,NULL,3,NULL);
  xTaskCreate(afficheIdleCoucnt,"proc libre",6000,NULL,3,NULL);
}
