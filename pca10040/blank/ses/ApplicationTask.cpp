#include "Tasks.h"

void ApplicationTask(void *pvParameter) {

  xEventGroupSetBits(taskStatusBitGroup, APPBIT);

  while (true) {
    vTaskDelay(500);
    xEventGroupSetBits(taskStatusBitGroup, APPBIT);
  }
}