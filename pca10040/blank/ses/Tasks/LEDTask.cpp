#include "Tasks.h"

void LEDTask(void *pvParameter) {
  //  DigitalIOPin led(LED_BLU, DigitalIOPin::output, DigitalIOPin::pullup);

  xEventGroupSetBits(taskStatusBitGroup, LEDBIT);

  while (true) {
    vTaskDelay(500);
    xEventGroupSetBits(taskStatusBitGroup, LEDBIT);
  }
}