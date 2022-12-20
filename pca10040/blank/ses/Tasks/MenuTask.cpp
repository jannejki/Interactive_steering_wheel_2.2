#include "Tasks.h"

void MenuTask(void *pvParameter) {

  xEventGroupSetBits(taskStatusBitGroup, MENUBIT);

  while (true) {

    xEventGroupSetBits(taskStatusBitGroup, MENUBIT );
    vTaskDelay(500);
  }
}