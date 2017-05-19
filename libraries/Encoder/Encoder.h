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

		float x;
		float y;
		float angle;
        
		const float unitsAxisWidth = 0.1102;
		const float radius = 0.032;				// radius wheels in meters
		float circumference;

		float boundAngle(float a);
	public:
		Encoder(int robot);
        
		void readEncoder(float a[]);
		void updateRelativePosition(float reading[2]);
		boolean checkDistanceDriven(float xStart, float yStart, float distance);
        
		float getX();
		float getY();
		float getAngle();
		String test();
};

#endif
