/*
 ===============================================================================
 Name        : Steering wheel 2.1
 Author      : JKi
 Version     :
 Copyright   :
 Description : 
 Path        :D:\Ohjelmien tallennushommat yms\segger\examples\projects\steering-wheel-freertos\pca10040\blank\ses\main.c
 ===============================================================================
 */


 /*****************************************************************************
 * Includes
 ****************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "sdk_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "bsp.h"
#include "nordic_common.h"
#include "nrf_drv_clock.h"
#include "sdk_errors.h"
#include "app_error.h"
#include "board_prod.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"

#include "nrf_drv_saadc.h"

 /*****************************************************************************
 * Steering Wheel -specific includes
 ****************************************************************************/
#include "DigitalIOPin.h"



/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
#define TASK_DELAY        500           /**< Task delay. Delays a LED0 task for 500 ms */


 /*****************************************************************************
 * Tasks
 ****************************************************************************/
static void led_toggle_task_function (void * pvParameter)
{
    DigitalIOPin led(LED_BLU, DigitalIOPin::output);
    while (true)
    {
        led.write(true);
        vTaskDelay(TASK_DELAY);
       led.write(false);
        vTaskDelay(TASK_DELAY);
    }
}


/*****************************************************************************
 * Public functions
 ****************************************************************************/
int main(void)
{
    ret_code_t err_code;

    /* Initialize clock driver for better time accuracy in FREERTOS */
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);


    /* Create task for LED0 blinking with priority set to 2 */
    xTaskCreate(led_toggle_task_function, "LED0", configMINIMAL_STACK_SIZE, NULL, 2, NULL);


    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();

    while (true)
    {
        /* FreeRTOS should not be here... FreeRTOS goes back to the start of stack
         * in vTaskStartScheduler function. */
    }
}

/**
 *@}
 **/
