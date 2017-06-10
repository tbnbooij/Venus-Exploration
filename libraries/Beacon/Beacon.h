#ifndef Beacon_h
#define Beacon_h

#include "Arduino.h"

class Beacon
{
	private:
    uint8_t LDRPin;
    short rAve[3];
    uint8_t iterator = 0;
    short maxVal[2] = {0};
	public:
    Beacon(uint8_t pin);
    void start();
    void measure();
    int stop();
};

#endif
