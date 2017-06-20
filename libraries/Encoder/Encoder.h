#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

class Encoder
{
	private:
		int pinLeft;
		int pinRight;

		int leftEncoderState;
		int lastLeftEncoderState;
		int rightEncoderState;
		int lastRightEncoderState;

		float x = 0;
		float y = 0;
		float angle = 0;
		
		float xStart = 0;
		float yStart = 0;
		float angleStart = 0;
		
		float distanceToBeDriven;
		float angleToBeTurned;
		
		boolean turning = false;
		boolean driving = false;
        
		float unitsAxisWidth;
		float angleErrorPercentage;
		float radius;				// radius wheels in meters
		float circumference;
		
		float readLeftEncoder(int leftWheelStatus);
		float readRightEncoder(int rightWheelStatus);
	public:
		Encoder(int robot);
		void setup();
        
		void updateRelativePosition(int leftWheelStatus, int rightWheelStatus);
		boolean checkDistanceDriven(float distance);
		boolean checkAngleTurned(float a);
        
		float getX();
		float getY();
		float getAngle();
		float getRawAngle();
		String test();
		
		float boundAngle(float a);
		float getTurnAngle();
};

#endif

