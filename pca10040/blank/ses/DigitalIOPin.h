#include <cstdint>
#include "bsp.h"

class DigitalIOPin 
{
  	public:
        enum pinMode {output, input};
        enum pullDir {pullup, pulldown};

        DigitalIOPin(uint32_t pin, pinMode mode);
	DigitalIOPin(uint32_t pin, pinMode mode, pullDir dir, bool invert);
        virtual ~DigitalIOPin();

        uint32_t read();
        void write(bool state);

        private:
        uint32_t pin;
        bool invert;
};