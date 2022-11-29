#ifndef DISPLAY_H
#define DISPLAY_H

#include "I2C.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LCD_SLAVE_ADDR 0x3C
#define SET_DDRAM_ADDR 0x80

class Display {
public:
  Display(I2C *i2c);
  virtual ~Display();

  void init();
  void sendCmd(uint8_t data);
  void sendData(uint8_t data);
  void print(char string[80]);
  void setCursor(int x, int y);
  void clearScreen();

private:
  I2C *i2c;
  uint8_t _rowOffsets[4] = {0x00, 0x20, 0x40, 0x60};
};

#endif