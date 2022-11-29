#ifndef TASKS_H
#define TASKS_H

/*****************************************************************************
 * Board and FreeRTOS -related includes
 ****************************************************************************/
#include "FreeRTOS.h"
#include "nrf_drv_saadc.h"

/*****************************************************************************
 * Steering wheel -related includes
 ****************************************************************************/
#include "DigitalIOPin.h"
#include "I2C.h"
#include "Display.h"
#include "Potentiometer.h"
#include "board_prod.h"


/*****************************************************************************
 * Task Definitions
 ****************************************************************************/
void LEDTask(void *pvParameter);
void MenuTask(void *pvParameter);
void WatchDogTask(void *pvParameter);
#endif