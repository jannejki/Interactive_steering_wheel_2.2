#include "Tasks.h"

void MenuTask(void *pvParameter) {
  I2C *i2c = static_cast<I2C *>(pvParameter);
  Display display(i2c);
  Potentiometer pot(NRF_SAADC_INPUT_AIN2, 5);

  char buff2[50];
  char buff[50];

  nrf_saadc_value_t adc_val;
  float sector;

  display.clearScreen();
  display.print("      STARTING");
  display.setCursor(0,1);
  display.print("   Steering wheel");


  xEventGroupSetBits(taskStatusBitGroup, MENUBIT);
  xEventGroupWaitBits(
      taskStatusBitGroup,
      ALLTASKS,
      pdFALSE,
      pdTRUE,
      portMAX_DELAY);

  while (true) {

    display.clearScreen();

    adc_val = pot.readRawValue();
    sprintf(buff, "POT val: %d ", adc_val);

    sector = pot.readSector();
    sprintf(buff2, "section: %d", (int)sector);

    display.print(buff);
    display.setCursor(0, 1);
    display.print(buff2);

    xEventGroupSetBits(taskStatusBitGroup, MENUBIT);
    vTaskDelay(500);
  }
}