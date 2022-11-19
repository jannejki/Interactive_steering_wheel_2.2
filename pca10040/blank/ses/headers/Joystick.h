#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "DigitalIOPin.h"
#include "board_prod.h"
#include "bsp.h"
#include <cstdint>

class Joystick {
public:
  Joystick();
  virtual ~Joystick();

private:
  DigitalIOPin *left;
  DigitalIOPin *right;
  DigitalIOPin *up;
  DigitalIOPin *down;
  DigitalIOPin *center;
};

#endif