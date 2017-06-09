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
		
		int sensorPinline1;
		int sensorPinline2;
		
		int channel = 0;
		int sensormax = 0;
		int sensorvalue = 0;
		
		int threshold = 180;
		int thing = 0;
	public:
		IR(int robot);
		
		
}