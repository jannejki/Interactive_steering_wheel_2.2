#include "Potentiometer.h"

Potentiometer::Potentiometer(nrf_saadc_input_t _input, int _secW) : input(_input), sectionWidth(_secW) {
  saadc_init();
}

Potentiometer::~Potentiometer() {
}

nrf_saadc_value_t Potentiometer::readRawValue() {
  nrf_saadc_value_t adc_val;
  nrfx_saadc_sample_convert(0, &adc_val);
  return adc_val;
}

float Potentiometer::readSector() {
  nrf_saadc_value_t adc_val;
  float result;
  nrfx_saadc_sample_convert(0, &adc_val);
  result = ((float)adc_val/maxVal)*100.0;
  float mod = (int)result % sectionWidth;
  result = result - mod;
  return result;
}

/*****************************************************************************
 * Private functions
 ****************************************************************************/
void Potentiometer::saadc_callback_handler(nrf_drv_saadc_evt_t const *p_event) {
  // empty
}

void Potentiometer::saadc_init() {
  ret_code_t err_code;

  nrf_saadc_channel_config_t channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(input);

  err_code = nrf_drv_saadc_init(NULL, saadc_callback_handler);
  APP_ERROR_CHECK(err_code);

  err_code = nrfx_saadc_channel_init(0, &channel_config);
  APP_ERROR_CHECK(err_code);
}