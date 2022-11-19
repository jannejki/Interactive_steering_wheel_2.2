#include "I2C.h"

I2C::I2C() {
  ret_code_t err_code;
  m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

  const nrf_drv_twi_config_t twi_config = {
      .scl = SCLKPIN,
      .sda = SDAPIN,
      .frequency = NRF_DRV_TWI_FREQ_400K,
      .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
      .clear_bus_init = false};

  err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
  APP_ERROR_CHECK(err_code);

  nrf_drv_twi_enable(&m_twi);
}

I2C::~I2C() {
}

ret_code_t I2C::sendData(uint8_t *tx_data, uint8_t address, uint8_t length) {
  ret_code_t err_code;
  err_code = nrf_drv_twi_tx(&m_twi, address, tx_data, length, false);
  APP_ERROR_CHECK(err_code);
  nrf_delay_ms(1);

  return err_code;
}