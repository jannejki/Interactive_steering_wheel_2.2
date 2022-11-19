#include "Joystick.h"

Joystick::Joystick() {
  left = new DigitalIOPin(JOY_0, DigitalIOPin::output, DigitalIOPin::pullup);
  left = new DigitalIOPin(JOY_1, DigitalIOPin::output, DigitalIOPin::pullup);
  left = new DigitalIOPin(JOY_2, DigitalIOPin::output, DigitalIOPin::pullup);
  left = new DigitalIOPin(JOY_3, DigitalIOPin::output, DigitalIOPin::pullup);
  left = new DigitalIOPin(JOY_4, DigitalIOPin::output, DigitalIOPin::pullup);
}

Joystick::~Joystick() {
}