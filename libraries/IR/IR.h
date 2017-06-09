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
		int rockChannel = 0;
		int rockSensorValueHighest =0;
		int rockSensorValueMax = 0;
		int rockSensor4Value=0;
		int rockSensor5Value=0;
		int rockSensorValueValidated = 0;
		int rockSensorValue = 0;
		int rockSensorThresholdValue = 80;
		int maxRockSensorValue = 120;
		int minRockSensorValue = 1000;
		
		int readRockSensor();

		
		int threshold = 180;
		int thing = 0;
	public:
		IR(int robot);
		void selectChannel(int channel);
		float findAngleRockRobot(int rockChannel);
		void setup();
		int readLineSensor();
		
		
};

#endif
