#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

class Encoder
{
	private:
		int _pinLeft;
		int _pinRight;

		int leftEncoderState;
		int lastLeftEncoderState;
		int rightEncoderState;
		int lastRightEncoderState;

		float x;
		float y;
		float angle;
        
        const float unitsAxisWidth = 1;
        const float radius = 1;
        float circumference;

		float boundAngle(float a);
	public:
		Encoder(int pinLeft, int pinRight);
        
		void readEncoder(float a[]);
		void updateRelativePosition(float reading[2]);
		void checkDistanceDriven(float xStart, float yStart, float distance);
        
		float getX();
		float getY();
		float getAngle();
};

#endif
