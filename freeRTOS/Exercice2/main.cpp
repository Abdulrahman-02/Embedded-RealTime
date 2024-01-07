#include <Arduino.h>

void TaskOne(void * pvParameters) {
  while(true) {
    Serial.println("Hello from task 1");
    delay(2000);
  }
}

void TaskTwo(void * pvParameters) {
  while(true) {
    Serial.println("Hello from task 2");
    delay(2000);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  xTaskCreate(TaskOne,"Task 1",1024,NULL,1,NULL);
  xTaskCreate(TaskTwo,"Task 2",1024,NULL,1,NULL);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

/*
 * La tache la plus prioritaire passe en premier
 * si meme priorité chaque tache s'execute pour un moment après l'autre passe ainsi de suite (temps partagé)
 * Modifier l'exercice pour afficher l'id du core sur lequel s'execute chaque tache ==>
 * Modifier l'exercice pour exécuter la tache 1 sur le core 1 et la tache 2 sur le core 0
 * Modifier l'exercice en affectant des priorités différentes aux taches
 * Modifier l'exercice en affectant des priorités différentes aux taches
 * */
 
TaskHandle_t TaskOneHandle;
TaskHandle_t TaskTwoHandle;


void TaskOne(void * pvParameters) {
  while(true) {
    Serial.println("Hello from task 1");
    Serial.println(xTaskGetAffinity(TaskOneHandle));
    delay(2000);
  }
}

void TaskTwo(void * pvParameters) {
  while(true) {
    Serial.println("Hello from task 2");
    Serial.println(xTaskGetAffinity(TaskTwoHandle));
    delay(2000);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  xTaskCreatePinnedToCore(TaskOne, "Task 1", 1024, NULL, 1, &TaskOneHandle, 0);
  xTaskCreatePinnedToCore(TaskTwo, "Task 2", 1024, NULL, 1, &TaskOneHandle, 1);
}

/*
* Modifier la dernière version de l'exercice 2.2 en bloquant chaque tache pendant 100 ms après chaque affichage. Que remarquez-vous?
*/

vTaskDelay(2000 / portTICK_PERIOD_MS);


/*
* Ecrire une application contenant une tache dont le role est d'afficher une valeur
* Lancer deux instances de cette tache en transmettant à chacune la valeur à afficher
* Les deux instances auront la meme priorité
*/

TaskHandle_t TaskHandle1;
TaskHandle_t TaskHandle2;

void DisplayValueTask(void *pvParameters) {
  int valueToDisplay = *((int*)pvParameters);

  while (1) {
    Serial.print("Task ");
    Serial.print(xTaskGetHandleToTaskName(NULL));
    Serial.print(" - Value to Display: ");
    Serial.println(valueToDisplay);
    delay(2000);
  }
}

void setup() {
  Serial.begin(115200);

  int valueForTask1 = 42;
  int valueForTask2 = 73;

  xTaskCreatePinnedToCore(DisplayValueTask, "Task1", 1024, &valueForTask1, 1, &TaskHandle1, 0);
  xTaskCreatePinnedToCore(DisplayValueTask, "Task2", 1024, &valueForTask2, 1, &TaskHandle2, 1);
}

