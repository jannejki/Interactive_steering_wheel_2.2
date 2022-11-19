#include "DigitalIOPin.h"

DigitalIOPin::DigitalIOPin(int pin_, pinMode mode, pullDir dir, bool invert) : pin(pin_), inv(invert) {
  if (mode == output) {
    nrf_gpio_cfg_output(pin_);
  } else if (mode == input && dir == pullup) {
    nrf_gpio_cfg_sense_input(pin, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
  } else if (mode == input && dir == pulldown) {
    nrf_gpio_cfg_sense_input(pin, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_LOW);
  }
}

DigitalIOPin::~DigitalIOPin() {
  nrf_gpio_pin_clear(this->pin);
}

void DigitalIOPin::write(bool state) {
  nrf_gpio_pin_write(pin, state);
}

uint32_t DigitalIOPin::read() {
  bool state = nrf_gpio_pin_read(this->pin);
  if (inv) {
    return !state;
  } else {
    return state;
  }
}