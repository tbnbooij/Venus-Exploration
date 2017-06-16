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
		float rockSensor4Value=0;
		float rockSensor5Value=0;
		int rockSensorValueValidated = 0;
		int rockSensorValue = 0;
		int rockSensorThresholdValue = 220;
		float maxRockSensorValue = 120;
		float minRockSensorValue = 1000;

		
		int threshold = 160;
	public:
		IR(int robot);
		void selectChannel(int channel);
		float findAngleRockRobot(int rockChannel);
		void setup();
		int readLineSensor();
		
		int readRockSensor();
};

#endif
