#include "Motion.h"
#include "Arduino.h"
#include "Servo.h"

Motion::Motion(int robot) {
	if(robot == 1) {
		pingPin = 9; //robot 1:9 robot 2:9
		ultraSoundServo = 10; //robot 1:10 robot 2:11
		servoLeftPin = 13; //robot 1:13 robot 2:12
		servoRightPin = 12; //robot 1:12 robot 2:13
		servoGrabPin = 11; //robot 1:11 robot 2:10
		normal = 74;
	} else if(robot == 2) {
		pingPin = 9; //robot 1:9 robot 2:9
		ultraSoundServo = 11; //robot 1:10 robot 2:11
		servoLeftPin = 12; //robot 1:13 robot 2:12
		servoRightPin = 13; //robot 1:12 robot 2:13
		servoGrabPin = 10; //robot 1:11 robot 2:10
		normal = 84;
	}

	degreeRight = normal - deviationNormal;
	degreeLeft = normal + deviationNormal;
}

void Motion::setup() {
	servoUltrasound.attach(ultraSoundServo);
	ultrasoundAngle = degreeRight;
    servoUltrasound.write(ultrasoundAngle);
	closeGrabber();

}

String Motion::test() {
	return "1";
}

int Motion::positionWall(){
	int m;
	if(firstPositioningWall == true) {
		ultrasoundAngle = 0;
		servoUltrasound.write(ultrasoundAngle);
		delay(200);

		m = measurement();
		if(m > 100) {
			m = 100;
		}

		measurementRef = m;
	} else {
		servoUltrasound.write(ultrasoundAngle);
		delay(7);
		m = measurement();
		if(m > 100) {
			m = 100;
		}
	}

	firstPositioningWall = false;
	if(m > measurementRef){
		return ultrasoundAngle-1;

	}
	else {
		measurementRef = m;
		ultrasoundAngle++;
		return -1;
	}

}

void Motion::turnHead() {
	if(ultrasoundGoingLeft == 1) {
		if(ultrasoundAngle < degreeLeft) {
			ultrasoundAngle++;
		} else {
			ultrasoundGoingLeft = 0;
			ultrasoundAngle--;

		}
	} else {
		if(ultrasoundAngle > degreeRight) {
			ultrasoundAngle--;
		} else {
			ultrasoundGoingLeft = 1;
			ultrasoundAngle++;
		}
	}
	servoUltrasound.write(ultrasoundAngle);
	delay(ultraServoDelay);
}

int Motion::measureUltrasoundWithoutTurning() {
	// Make something that turns right after detecting on the left and vice versa!!
	if(measurement() < maxDistance){
		return ultrasoundAngle;
	} else {
		return -1;
	}
}

int Motion::measureUltrasound() {
	turnHead();
	return measureUltrasoundWithoutTurning();
}


float Motion::measurement(){
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  float duration, cm;



  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance

  return microsecondsToCentimeters(duration);

}

float Motion::microsecondsToCentimeters(float microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void Motion::turnAfterObstacle(int angle){
    servoLeft.attach(servoLeftPin);
    servoRight.attach(servoRightPin);
    if (angle > normal ){
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1700);
	  leftWheelStatus = 1;
	  rightWheelStatus = -1;
    }
    if (angle <= normal ){
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1300);
	  leftWheelStatus = -1;
	  rightWheelStatus = 1;
    }
    delay(turnTime);
    stopDriving();
}

void Motion::turnLeft() {
	servoLeft.attach(servoLeftPin);
    servoRight.attach(servoRightPin);
	servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1300);
	leftWheelStatus = -1;
	rightWheelStatus = 1;
}
void Motion::turnLeftCliff() {
	servoLeft.attach(servoLeftPin);
    servoRight.attach(servoRightPin);
	servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1300);
	delay(500);
	leftWheelStatus = -1;
	rightWheelStatus = 1;
}

void Motion::turnRight() {
	servoLeft.attach(servoLeftPin);
    servoRight.attach(servoRightPin);
	servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1700);
	leftWheelStatus = 1;
	rightWheelStatus = -1;
}
void Motion::turnRightCliff() {
	servoLeft.attach(servoLeftPin);
    servoRight.attach(servoRightPin);
	servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1700);
	delay(200);
	leftWheelStatus = 1;
	rightWheelStatus = -1;
}

void Motion::startDriving() {
	servoLeft.attach(servoLeftPin);
    servoRight.attach(servoRightPin);
    servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
    servoRight.writeMicroseconds(1300);        // Right wheel clockwise
	leftWheelStatus = 1;
	rightWheelStatus = 1;
}

void Motion::startDrivingBackwards() {
	servoLeft.attach(servoLeftPin);
    servoRight.attach(servoRightPin);
    servoLeft.writeMicroseconds(1300);         // Left wheel counterclockwise
    servoRight.writeMicroseconds(1700);        // Right wheel clockwise
	leftWheelStatus = -1;
	rightWheelStatus = -1;
}

void Motion::stopDriving(){
    servoLeft.detach();
    servoRight.detach();
	leftWheelStatus = 0;
	rightWheelStatus = 0;
}

void Motion::openGrabber(){
	// first robot
	if(servoGrabPin == 11) {
		servoGrab.attach(servoGrabPin);
		servoGrab.write(180);
	}
	// second robot
	else {
		servoGrab.attach(servoGrabPin);
		servoGrab.write(0);
	}
}

void Motion::closeGrabber(){
	// first robot
	if(servoGrabPin == 11) {
		servoGrab.attach(servoGrabPin);
		servoGrab.write(0);
	}
	// second robot
	else {
		servoGrab.attach(servoGrabPin);
		servoGrab.write(180);
	}
}
