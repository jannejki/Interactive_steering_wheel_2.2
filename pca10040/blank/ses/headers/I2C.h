#ifndef I2C_H
#define I2C_H

#include "board_prod.h"
#include "nrf_delay.h"
#include "nrf_drv_twi.h"
#include "nrfx_twi.h"
#include "nrfx_twi_twim.h"
#include "nrfx_twim.h"
#include <cstdint>

#define TWI_INSTANCE_ID 0

class I2C {
public:
  I2C();
  virtual ~I2C();
  ret_code_t sendData(uint8_t *tx_data, uint8_t address, uint8_t length);

private:
  nrf_drv_twi_t m_twi;
};
#endif