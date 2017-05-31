#include "Encoder.h"
#include "Arduino.h"
#include "Math.h"

Encoder::Encoder(int robot) {
	if(robot == 1) {
		
		angleErrorPercentage = 1.05; // 1.0 would be no error
	} else {
		angleErrorPercentage = 1;
	}
	
	pinLeft = 7;
	pinRight = 8;
	radius = 0.03435;
	unitsAxisWidth = 0.1102;
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
	
	if(leftDelta == 0 && rightDelta == 0) {
		return;
	}

	// leftDelta and rightDelta = distance that the left and right wheel have moved along
	//  the ground
	// https://robotics.stackexchange.com/questions/1653/calculate-position-of-differential-drive-robot
	if (leftWheelStatus == 1 && rightWheelStatus == 1) { // Going straight
		x = x + leftDelta * cos(angle);
		y = y + rightDelta * sin(angle);
	} else {
		// rotating half the unitsAxisWidth with both encoders would be 2*PI
		float deltaAngle = (( abs(leftDelta) + abs(rightDelta) ) / unitsAxisWidth ) * angleErrorPercentage;
		
		if(leftWheelStatus == 1 && rightWheelStatus == -1) {
			angle -= deltaAngle;
		} 
		
		if(leftWheelStatus == -1 && rightWheelStatus == 1) {
			angle += deltaAngle;
		}
	}
}

boolean Encoder::checkDistanceDriven(float xStart, float yStart, float distance) {
	if(distance > 0) { // set when starting driving
		return sqrt(pow(x-xStart, 2)+pow(y-yStart,2)) >= distance;
	}
}

boolean Encoder::checkAngleTurned(float begin, float a, boolean increasing) {
	if(increasing) {
		return begin + a <= angle;
	} else {
		return begin - a >= angle;
	}
}

float Encoder::boundAngle(float a) {
	while(a < 0) {
		a += 2*M_PI;
	}

	while(a > 2*M_PI) {
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