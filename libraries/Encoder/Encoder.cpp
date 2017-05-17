#include "Encoder.h"
#include "Arduino.h"

Encoder::Encoder(int pinLeft, int pinRight) {
	_pinLeft = pinLeft;
	_pinRight = pinRight;

	pinMode(pinLeft, INPUT);
	pinMode(pinRight, INPUT);
}

void Encoder::readEncoder(float a[]) {
	float leftDelta = 0.0;
	float rightDelta = 0.0;

	leftEncoderState = digitalRead(_pinLeft);
	if(leftEncoderState != lastLeftEncoderState) {
		if(leftEncoderState == HIGH) {
			//rising trigger
			leftDelta = circumference / 8;
		}
	}
	lastLeftEncoderState = leftEncoderState;

	rightEncoderState = digitalRead(_pinRight);
	if(rightEncoderState != lastRightEncoderState) {
		if(rightEncoderState == HIGH) {
			//rising trigger
			rightDelta = circumference / 8;
		}
	}
	lastRightEncoderState = rightEncoderState;

	a[0] = leftDelta;
	a[1] = rightDelta;
}

void Encoder::updateRelativePosition(float reading[2]) {
	float leftDelta = reading[0];
		float rightDelta = reading[1];

		// leftDelta and rightDelta = distance that the left and right wheel have moved along
		//  the ground
		// https://robotics.stackexchange.com/questions/1653/calculate-position-of-differential-drive-robot
		if (fabs(leftDelta - rightDelta) < 1.0e-6) { // basically going straight
			x = x + leftDelta * cos(angle);
			y = y + rightDelta * sin(angle);
		} else {
			float R = unitsAxisWidth * (leftDelta + rightDelta) / (2 * (rightDelta - leftDelta));
			float wd = (rightDelta - leftDelta) / unitsAxisWidth;

			x = x + R * sin(wd + angle) - R * sin(angle);
			y = y - R * cos(wd + angle) + R * cos(angle);
			angle = boundAngle(angle + wd);
		}
}

boolean Encoder::checkDistanceDriven(float xStart, float yStart, float distance) {
	if(distance > 0) { // set when starting driving
		return sqrt(pow(x-xStart, 2)+pow(y-yStart,2)) >= distance;
	}
}

float Encoder::boundAngle(float a) {
	if(a < 0) {
		a += 2*M_PI;
	}

	if(a > 2*M_PI) {
		a -= 2* M_PI;
	}
	return a;
}

float Encoder::getX() {
	return x;
}

float Encoder::getY() {
	return y;
}

float Encoder::getAngle() {
	return angle;
}

String Encoder::test() {
	return "1";
}