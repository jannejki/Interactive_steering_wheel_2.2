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
EventGroupHandle_t taskStatusBitGroup;
TimerHandle_t taskTimeoutTimer;

/*****************************************************************************
 * Public functions
 ****************************************************************************/

int main(void) {
  ret_code_t err_code;

  /* Initialize clock driver for better time accuracy in FREERTOS */
  err_code = nrf_drv_clock_init();
  APP_ERROR_CHECK(err_code);

  taskStatusBitGroup = xEventGroupCreate();
  taskTimeoutTimer = xTimerCreate("Task timeout", WATCHDOG_TIMEOUT, pdFALSE, (void *)0, taskTimeOutCallback);

  xTaskCreate(ECUTask, "ECUTask", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
              (TaskHandle_t *)NULL);

  xTaskCreate(ApplicationTask, "Application", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
              (TaskHandle_t *)NULL);

  xTaskCreate(MenuTask, "Menu", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
              (TaskHandle_t *)NULL);

  xTaskCreate(LEDTask, "LEDTask", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
              (TaskHandle_t *)NULL);

  xTaskCreate(WatchDogTask, "WatchDog", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY) + 1UL,
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