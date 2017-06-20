#ifndef Beacon_h
#define Beacon_h
#define ROLL_AVE_SIZE 10

#include "Arduino.h"
#include "Servo.h"

class Beacon
{
	private:
    		uint8_t LDRPin;
    		short rAve[ROLL_AVE_SIZE];
	public:
    		Beacon(uint8_t pin);
    		void start();
		short maxVal[2] = {0};
    		int measure(int angle, int left, int right, Servo servo);
};

#endif
