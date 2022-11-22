#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "nrf_drv_saadc.h"
#include <math.h>


class Potentiometer {
  public:
  Potentiometer(nrf_saadc_input_t input, int _secW);
  virtual ~Potentiometer();
  nrf_saadc_value_t readRawValue();
  float readSector();

  private:
  static void saadc_callback_handler(nrf_drv_saadc_evt_t const * p_event);
  void saadc_init();
  
  float maxVal = 804;
  int sectionWidth;
  

  nrf_saadc_input_t input;
};

#endif