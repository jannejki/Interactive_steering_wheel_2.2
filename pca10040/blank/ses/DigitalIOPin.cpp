#include "DigitalIOPin.h"

DigitalIOPin::DigitalIOPin (uint32_t pin, pinMode mode, pullDir dir,  bool invert) {
  if(mode == output) {
    nrf_gpio_cfg_output(pin);
  } else if(mode == input && dir == pullup) {
    nrf_gpio_cfg_sense_input (pin, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
  } else if(mode == input && dir == pulldown) {
    nrf_gpio_cfg_sense_input (pin, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_LOW);
  }

  this->pin = pin;
  this->invert = invert;
}

DigitalIOPin::DigitalIOPin (uint32_t pin, pinMode mode) {
  DigitalIOPin(pin, mode, DigitalIOPin::pullup, false);
}

DigitalIOPin::~DigitalIOPin() {
  nrf_gpio_pin_clear(this->pin);
}


void DigitalIOPin::write(bool state) {
  nrf_gpio_pin_write(this->pin, state);
}


uint32_t DigitalIOPin::read() {
  bool state =  nrf_gpio_pin_read(this->pin);
  if(this->invert) {
    return !state;
  } else {
    return state;
  }
}
