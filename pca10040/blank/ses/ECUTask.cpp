#include "Tasks.h"

void ECUTask(void *pvParameter) {
  xEventGroupSetBits(taskStatusBitGroup, ECUBIT);

  while (1) {
    vTaskDelay(500);
    xEventGroupSetBits(taskStatusBitGroup, ECUBIT);
  }
}