#ifndef DIGITALIOPIN_H
#define DIGITALIOPIN_H

#include "bsp.h"
#include <cstdint>

class DigitalIOPin {
public:
  enum pinMode { output,
                 input };
  enum pullDir { pullup,
                 pulldown };

  DigitalIOPin(int pin, pinMode mode, pullDir dir, bool invert = false);
  virtual ~DigitalIOPin();

  uint32_t read();
  void write(bool state);

private:
  int pin;
  bool inv;
};

#endif