#include "Tasks.h"

void WatchDogTask(void *pvParameter) {
 
 while(1) {
  vTaskDelay(WATCHDOG_TIMEOUT);
 }
}