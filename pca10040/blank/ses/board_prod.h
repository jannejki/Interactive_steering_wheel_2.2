#ifndef BOARD_PROD_H
#define BOARD_PROD_H

#include "FreeRTOS.h"
#include "event_groups.h"
#include "nordic_common.h"
#include "nrf_gpio.h"
#include "queue.h"
#include <mutex>
#include "semphr.h"

/*****************************************************************************
 * Board pins
 ****************************************************************************/
// LED
#define LED_BLU 22

// Battery system pins
#define BT_SELI 28 // Current select, low = 100mA, high = 500mA
#define BT_SELV 27 // Voltage select, low = 4.1V, high = 4.2V
#define BT_CHG 26  // Charge sensing pin
#define BT_CHG_EN 29

// Buttons
#define BTN_0 14
#define BTN_1 13
#define BTN_2 12
#define BTN_3 11

// Joystick
#define JOY_0 15
#define JOY_1 16
#define JOY_2 17
#define JOY_3 18
#define JOY_4 19

// Potentiometers, use NRF_SAADC_INPUT_AINx as found in nrf_saadc.h instead
#define POT_0 4
#define POT_1 5

// TWI display for display, plus control pins
#define SCLKPIN 8
#define SDAPIN 7
#define RES_DISP 6
#define SA0 9

/*****************************************************************************
 * Times
 ****************************************************************************/
#define TASK_DELAY 500
#define WATCHDOG_TIMEOUT 10000


/*****************************************************************************
 * Task monitoring flags
 ****************************************************************************/
#define ECUBIT   (1 << 0)
#define LEDBIT   (1 << 1)
#define MENUBIT  (1 << 2)
#define APPBIT   (1 << 3)
#define ALLBITS  (ECUBIT | LEDBIT | MENUBIT | APPBIT)

/*****************************************************************************
 * Public variables
 ****************************************************************************/
 /*
enum Status {
  OK,
  DISCONNECTED,
  TASK_FAIL,
  STARTUP
};

// dummy modes, change names to correct ones
enum Mode {
  MODE1 = 0,
  MODE2 = 1,
  MODE3 = 2,
};

struct AppMode {
  Status status;
  Mode mode;
};

struct messageToMenu {
  bool RW;
  AppMode *app;
  uint8_t rxData;
  uint8_t memory;
};

struct MessageFromMenu {
  bool RW;
  uint8_t txData;
  Mode mode;
  uint8_t memory;
};

struct MessageToECU {
  bool RW;
  uint8_t memory;
  uint8_t *data;
};

struct MessageFromECU {
  bool RW;
  int rxData;
  uint16_t i2cStatus;
  uint8_t memory;
};

extern QueueHandle_t LEDQueue;
extern EventBits_t monitorBits;
extern SemaphoreHandle_t startSemaphore;*/

extern EventGroupHandle_t taskStatusBitGroup;
extern TimerHandle_t taskTimeoutTimer;

#endif