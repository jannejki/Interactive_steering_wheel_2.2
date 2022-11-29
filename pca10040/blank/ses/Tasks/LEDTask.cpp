#include "Tasks.h"

void LEDTask(void *pvParameter) {
  DigitalIOPin led(LED_BLU, DigitalIOPin::output, DigitalIOPin::pullup);
  Status status = STARTUP;
  int onTime;
  int offTime;

  vTaskDelay(5000); // For testing purposes
  monitorBits = xEventGroupSetBits(taskStatusBitGroup, LEDBIT);

  while (true) {
    led.write(true);
    vTaskDelay(onTime);
    led.write(false);
    vTaskDelay(offTime);

    xQueueReceive(LEDQueue, &status, (TickType_t)0);

    switch (status) {
    case OK:
      onTime = 1000;
      offTime = 3000;
      break;
    case DISCONNECTED:
      onTime = 500;
      offTime = 500;
      break;
    case TASK_FAIL:
      onTime = 5000;
      offTime = 5000;
      break;
    case STARTUP:
      onTime = 100;
      offTime = 100;
      break;
    }
  }
}