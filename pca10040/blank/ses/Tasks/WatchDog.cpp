#include "Tasks.h"

void WatchDogTask(void *pvParameter) {

  xEventGroupWaitBits(taskStatusBitGroup, ALLBITS, pdFALSE, pdTRUE, portMAX_DELAY);

  while (1) {
    vTaskDelay(500);
  }
}

void taskTimeOutCallback(TimerHandle_t xTimer) {

}