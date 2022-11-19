#include "Display.h"
Display::Display(I2C *i2c_) : i2c(i2c_) {
  init();
}

Display::~Display() {
}

void Display::init() {
  nrf_gpio_cfg_output(RES_DISP);
  nrf_gpio_cfg_output(SA0);
  nrf_gpio_pin_set(RES_DISP);
  nrf_gpio_pin_clear(SA0);
  nrf_delay_ms(100);
  sendCmd(0x2A);  // function set (extended command set)
  sendCmd(0x71);  // function selection A
  sendData(0x00); // disable internal VDD regulator (2.8V I/O). data(0x5C) = enable regulator (5V I/O)
  sendCmd(0x28);  // function set (fundamental command set)
  // not turning display off means it doesn't blink on re-init, so is silent error.
  // lcd_send_cmd(0x08); //display off, cursor off, blink off
  sendCmd(0x2A);  // function set (extended command set)
  sendCmd(0x79);  // OLED command set enabled
  sendCmd(0xD5);  // set display clock divide ratio/oscillator frequency
  sendCmd(0x70);  // set display clock divide ratio/oscillator frequency
  sendCmd(0x78);  // OLED command set disabled
  sendCmd(0x09);  // extended function set (4-lines)
  sendCmd(0x06);  // COM SEG direction
  sendCmd(0x72);  // function selection B
  sendData(0x00); // ROM CGRAM selection
  sendCmd(0x2A);  // function set (extended command set)
  sendCmd(0x79);  // OLED command set enabled
  sendCmd(0xDA);  // set SEG pins hardware configuration
  sendCmd(0x10);  // set SEG pins hardware configuration
  sendCmd(0xDC);  // function selection C
  sendCmd(0x00);  // function selection C
  sendCmd(0x81);  // set contrast control
  sendCmd(0x7F);  // set contrast control
  sendCmd(0xD9);  // set phase length
  sendCmd(0xF1);  // set phase length
  sendCmd(0xDB);  // set VCOMH deselect level
  sendCmd(0x40);  // set VCOMH deselect level
  sendCmd(0x78);  // OLED command set disabled
  sendCmd(0x28);  // function set (fundamental command set)
  // don't clear display, w're writing the whole thing anyway
  sendCmd(0x01); // clear display
  sendCmd(0x80); // set DDRAM address to 0x00
  sendCmd(0x0C); // display ON
  nrf_delay_ms(100);
}

void Display::sendCmd(uint8_t data) {
  uint8_t data_t[] = {0x80, data};
  i2c->sendData(data_t, LCD_SLAVE_ADDR, sizeof(data_t));
  nrf_delay_ms(1);
}

void Display::sendData(uint8_t data) {
  uint8_t data_t[] = {0x40, data};
  i2c->sendData(data_t, LCD_SLAVE_ADDR, sizeof(data_t));
  nrf_delay_ms(1);
}

void Display::sendString(char string[80]) {
  uint8_t length = strlen(string);
  for (uint8_t i = 0; i < length; i++) {
    sendData(string[i]);
  }
}

void Display::setCursor(int x, int y) {
  uint8_t DDRAM_addr = SET_DDRAM_ADDR | (_rowOffsets[y] + x);
  sendCmd(DDRAM_addr);
}

void Display::clearScreen() {
  sendCmd(0x01);
  setCursor(0,0);
}