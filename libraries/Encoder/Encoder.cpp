#include "Encoder.h"
#include "Arduino.h"
#include "Math.h"

Encoder::Encoder(int robot) {
	if(robot == 1) {
		pinLeft = 7;
		pinRight = 8;
		radius = 0.03435;
	} else {
		pinLeft = 7;
		pinRight = 8;
		radius = 0.034;
	}
}

void Encoder::setup() {
	pinMode(pinLeft, INPUT);
	pinMode(pinRight, INPUT);
	
	circumference = M_PI * 2 * radius;
}

float Encoder::readLeftEncoder(int leftWheelStatus) {
	float leftDelta = 0.0;

	leftEncoderState = digitalRead(pinLeft);
	if(leftEncoderState != lastLeftEncoderState) {
		if(leftEncoderState == HIGH) {
			
			//rising trigger
			if(leftWheelStatus == 1) {
				leftDelta = circumference / 8;
			}
			
			if(leftWheelStatus == -1) {
				leftDelta = -circumference / 8;
			}
		}
	}
	lastLeftEncoderState = leftEncoderState;

	return leftDelta;
}

float Encoder::readRightEncoder(int rightWheelStatus) {
	float rightDelta = 0.0;
	
	rightEncoderState = digitalRead(pinRight);
	if(rightEncoderState != lastRightEncoderState) {
		if(rightEncoderState == HIGH) {
			//rising trigger
			
			if(rightWheelStatus == 1) {
				rightDelta = circumference / 8;
			}
			
			if(rightWheelStatus == -1) {
				rightDelta = -circumference / 8;
			}
		}
	}
	lastRightEncoderState = rightEncoderState;
	return rightDelta;
}

void Encoder::updateRelativePosition(int leftWheelStatus, int rightWheelStatus) {
		float leftDelta = readLeftEncoder(leftWheelStatus);
		float rightDelta = readRightEncoder(rightWheelStatus);

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
			angle = angle + wd;
		}
}

boolean Encoder::checkDistanceDriven(float xStart, float yStart, float distance) {
	if(distance > 0) { // set when starting driving
		return sqrt(pow(x-xStart, 2)+pow(y-yStart,2)) >= distance;
	}
}

boolean checkAngleTurned(float begin, float a, boolean increasing) {
	if(increasing) {
		return begin + a <= angle;
	} else {
		return begin - a >= angle;
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
	return boundAngle(angle);
}

float Encoder::getRawAngle() {
	return angle;
}

String Encoder::test() {
	return "1";
}