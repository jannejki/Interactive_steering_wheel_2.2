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
#include "sdk_config.h"
#include "sdk_errors.h"
#include "task.h"
#include "timers.h"

#include "nrf_drv_saadc.h"

/*****************************************************************************
 * Steering Wheel -specific includes
 ****************************************************************************/
#include "DigitalIOPin.h"
#include "Display.h"
#include "I2C.h"
#include "Potentiometer.h"

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
#define TASK_DELAY 500 /**< Task delay. Delays a LED0 task for 500 ms */

/*****************************************************************************
 * Tasks
 ****************************************************************************/
static void buttonExampleTask(void *pvParameter) {
  DigitalIOPin led(LED_BLU, DigitalIOPin::output, DigitalIOPin::pullup);
  xTaskGetTickCount();
  int i = 0;

  while (true) {
    led.write(true);
    vTaskDelay(TASK_DELAY);
    led.write(false);
    vTaskDelay(TASK_DELAY);
  }
}

static void displayExampleTask(void *pvParameter) {
  I2C *i2c = static_cast<I2C *>(pvParameter);
  Display display(i2c);

  Potentiometer pot(NRF_SAADC_INPUT_AIN2, 5);

  char buff2[50];
  char buff[50];

  nrf_saadc_value_t adc_val;
  float sector;

  while (true) {
    display.clearScreen();

    adc_val = pot.readRawValue();
    sprintf(buff, "Pot val: %d ", adc_val);

    sector = pot.readSector();
    sprintf(buff2, "section: %d", (int)sector);

    display.sendString(buff);
    display.setCursor(0, 1);
    display.sendString(buff2);

    vTaskDelay(500);
  }
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/
int main(void) {
  ret_code_t err_code;

  /* Initialize clock driver for better time accuracy in FREERTOS */
  err_code = nrf_drv_clock_init();
  APP_ERROR_CHECK(err_code);

  I2C *i2c = new I2C();

  /* Create task for display task with priority set to 2 */
  xTaskCreate(displayExampleTask, "displayExampleTask", configMINIMAL_STACK_SIZE + 128, i2c, (tskIDLE_PRIORITY + 1UL),
              (TaskHandle_t *)NULL);

  /* Create task for blinking led with priority set to 2 */
  xTaskCreate(buttonExampleTask, "buttonExampleTask", configMINIMAL_STACK_SIZE + 128, NULL, (tskIDLE_PRIORITY + 1UL),
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