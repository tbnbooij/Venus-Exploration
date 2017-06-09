#ifndef IR_h
#define IR_h

#include "Arduino.h"

class IR
{
	private:
		int sensorPin;
		int selectPin1;
		int selectPin2;
		int selectPin3;
		
		int channel = 0;
		int sensormax = 0;
		int sensorvalue = 0;
		
	public:
		IR(int robot);
		
		
};

#endif
