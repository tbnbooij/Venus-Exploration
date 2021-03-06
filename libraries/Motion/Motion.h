#ifndef Motion_h
#define Motion_h

#include "Arduino.h"
#include "Servo.h"

class Motion
{
	private:
		Servo servoLeft;                             // Declare left and right servos
		Servo servoRight;
		Servo servoGrab;

		boolean isDriving = false;
		float distance = 0;

		int pingPin;
		int ultraSoundServo;		                // Pin where the servo of the ultrasound sensor is connected
		int maxDistance = 35;                       // Distance detected where so stop driving
		int turnTime = 20;                         // Time to turn when detecting something
		int initialSetupUltrasoundServo = 100;      // Amount of time needed to return ultrasound servo to the initial position
		int servoLeftPin;		                    // Pin for left servo wheel
		int servoRightPin;      		            // Pin for right servo wheel
		int ultraServoDelay = 7;                    // Time the ultrasound servo needs to turn before meassuring can start again
		int servoGrabPin;
		int measurementRef = 0;
		boolean firstPositioningWall = true;
		int closedAngleWall = 0;
		int deviationNormal = 40;

	public:
		Motion(int robot);
		void setup();
		String test();
		int degreeRight;	                    // Amount of degrees on the left side of the ultrasound sensor
		int degreeLeft;                       // Amount of degrees on the right side of the ultrasound sensor
		int ultrasoundGoingLeft = 1;

		Servo servoUltrasound;


		int measureUltrasound();
		void turnHead();
		int measureUltrasoundWithoutTurning();
		float measurement();
		float microsecondsToCentimeters(float microseconds);
		void turnAfterObstacle(int angle);
		void startDriving();
		void startDrivingBackwards();
		void turnRight();
		void turnLeft();
		void stopDriving();
		void openGrabber();
		void closeGrabber();
		int leftWheelStatus;
		int rightWheelStatus;
		int normal;
		int positionWall();
		int ultrasoundAngle;
		void turnLeftCliff();
		void turnRightCliff();
};

#endif
