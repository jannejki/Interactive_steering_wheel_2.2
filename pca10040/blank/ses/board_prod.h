/*D:\Ohjelmien tallennushommat yms\segger\examples\projects\steering-wheel\pca10040\s132\ses\board_prod.h*/

#include "nrf_gpio.h"
#include "nordic_common.h"
//LED
#define LED_BLU  22
//Battery system pins
#define BT_SELI  28 //Current select, low = 100mA, high = 500mA
#define BT_SELV  27 //Voltage select, low = 4.1V, high = 4.2V
#define BT_CHG   26 //Charge sensing pin 
#define BT_CHG_EN 29
//Buttons
#define BTN_0    14
#define BTN_1    13
#define BTN_2    12
#define BTN_3    11
#define JOY_0    15
#define JOY_1    16
#define JOY_2    17
#define JOY_3    18
#define JOY_4    19
//Potentiometers, use NRF_SAADC_INPUT_AINx as found in nrf_saadc.h instead
#define POT_0    4
#define POT_1    5
//TWI display for display, plus control pins
#define SCLK     8
#define SDAPIN   7
#define RES_DISP 6
#define SA0      9