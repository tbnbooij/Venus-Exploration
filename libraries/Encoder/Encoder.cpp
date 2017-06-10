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
		// LOW for 6.5 out of 11.5, HIGH for 5 out of 11.5
		if(leftEncoderState == HIGH) {
			//rising trigger
			if(leftWheelStatus == 1) {
				leftDelta = circumference / 8 * (6.5 / 11.5);
			}
			
			if(leftWheelStatus == -1) {
				leftDelta = -circumference / 8 * (6.5 / 11.5);
			}
		} else {
			//rising trigger
			if(leftWheelStatus == 1) {
				leftDelta = circumference / 8 * (5 / 11.5);
			}
			
			if(leftWheelStatus == -1) {
				leftDelta = -circumference / 8 * (5 / 11.5);
			}
		}
	}
	lastLeftEncoderState = leftEncoderState;

	return leftDelta;
}

float Encoder::readRightEncoder(int rightWheelStatus) {
	float rightDelta = 0.0;
	
	rightEncoderState = digitalRead(pinRight);
	if(rightEncoderState == HIGH) {
		Serial.println(1);
	} else {
		Serial.println(0);
	}
	if(rightEncoderState != lastRightEncoderState) {
		// LOW for 6.5 out of 11.5, HIGH for 5 out of 11.5
		if(rightEncoderState == HIGH) {
			//rising trigger 
			if(rightWheelStatus == 1) {
				rightDelta = circumference / 8 * 6.5 / 11.5;
			}
			
			if(rightWheelStatus == -1) {
				rightDelta = -circumference / 8 * 6.5 / 11.5;
			}
		} else {
			//falling trigger
			if(rightWheelStatus == 1) {
				rightDelta = circumference / 8 * 5 / 11.5;
			}
			
			if(rightWheelStatus == -1) {
				rightDelta = -circumference / 8 * 5 / 11.5;
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

boolean Encoder::checkDistanceDriven(float distance) {
	if(distanceToBeDriven != distance) {
		xStart = x;
		yStart = y;
		distanceToBeDriven = distance;
	}
	
	boolean b = sqrt(pow(x-xStart, 2)+pow(y-yStart,2)) >= abs(distance);
	
	if(b) {
		distanceToBeDriven = 0;
	}
	return b;
}

boolean Encoder::checkAngleTurned(float a) {
	if(angleToBeTurned != a) {
		angleStart = angle;
		angleToBeTurned = a;
	}
	
	boolean b = false;
	
	if(a > 0) {
		b = angleStart + a <= angle;
	} else {
		b = angleStart - a >= angle;
	}
	
	if(b) {
		angleToBeTurned = 0;
	}
	return b;
}

float Encoder::boundAngle(float a) {
	while(a <= -1*M_PI) {
		a += 2*M_PI;
	}

	while(a > M_PI) {
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