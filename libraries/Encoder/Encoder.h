#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"
#include "Math.h"

class Encoder
{
	private:
		int pinLeft;
		int pinRight;

		int leftEncoderState;
		int lastLeftEncoderState;
		int rightEncoderState;
		int lastRightEncoderState;

		float x;
		float y;
		float angle;
        
		float unitsAxisWidth;
		float radius;				// radius wheels in meters
		float circumference;

		float boundAngle(float a);
	public:
		Encoder(int robot);
		void setup();
        
		float readLeftEncoder(int leftWheelStatus);
		float readRightEncoder(int rightWheelStatus);
		void updateRelativePosition(int leftWheelStatus, int rightWheelStatus);
		boolean checkDistanceDriven(float xStart, float yStart, float distance);
		boolean checkAngleTurned(float begin, float a, boolean increasing);
        
		float getX();
		float getY();
		float getAngle();
		float getRawAngle();
		String test();
};

#endif

