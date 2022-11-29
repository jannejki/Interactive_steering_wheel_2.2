/*
 ===============================================================================
 Name        : Interactive steering wheel
 Author      : JKi
 Version     : 2.2
 Copyright   :
 Description :
 Path        : ..segger\examples\projects\Interactive_steering_wheel_2.2\pca10040\blank\ses\main.cpp
 ===============================================================================
 */

/*****************************************************************************
 * Includes
 ****************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "FreeRTOS.h"
#include "app_error.h"
#include "board_prod.h"
#include "bsp.h"
#include "nordic_common.h"
#include "nrf_delay.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_twi.h"
#include "queue.h"
#include "sdk_config.h"
#include "sdk_errors.h"
#include "task.h"
#include "timers.h"

#include "nrf_drv_saadc.h"

/*****************************************************************************
 * Steering Wheel -specific includes
 ****************************************************************************/
#include "Tasks.h"

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
QueueHandle_t LEDQueue;
EventBits_t monitorBits;
EventGroupHandle_t taskStatusBitGroup;


/*****************************************************************************
 * Public functions
 ****************************************************************************/
bool initQueues(void) {
  LEDQueue = xQueueCreate(2, sizeof(Status));
  if(LEDQueue == NULL) {
    return false;
  }
  return true;
}

int main(void) {
  ret_code_t err_code;

  /* Initialize clock driver for better time accuracy in FREERTOS */
  err_code = nrf_drv_clock_init();
  APP_ERROR_CHECK(err_code);

  I2C *i2c = new I2C();
  initQueues();

  taskStatusBitGroup = xEventGroupCreate();

  /* Create task for display task with priority set to 2 */
  xTaskCreate(MenuTask, "Menu", configMINIMAL_STACK_SIZE + 128, i2c, (tskIDLE_PRIORITY + 1UL),
              (TaskHandle_t *)NULL);

  /* Create task for blinking led with priority set to 2 */
  xTaskCreate(LEDTask, "LEDTask", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY),
              (TaskHandle_t *)NULL);

                /* Create task for blinking led with priority set to 2 */
  xTaskCreate(WatchDogTask, "WatchDog", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY) + 2UL,
              (TaskHandle_t *)NULL);

  /* Start FreeRTOS scheduler. */
  vTaskStartScheduler();

  while (true) {
    /* FreeRTOS should not be here... FreeRTOS goes back to the start of stack
     * in vTaskStartScheduler function. */
  }
}

/**
 *@}
 **/