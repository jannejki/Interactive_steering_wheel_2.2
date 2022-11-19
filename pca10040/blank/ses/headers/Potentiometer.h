#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "nrf_drv_saadc.h"

class Potentiometer {
  public:
  Potentiometer(nrf_saadc_input_t input);
  virtual ~Potentiometer();
  nrf_saadc_value_t readValue();


  private:
  static void saadc_callback_handler(nrf_drv_saadc_evt_t const * p_event);
  void saadc_init();
  

  nrf_saadc_input_t input;
};

#endif