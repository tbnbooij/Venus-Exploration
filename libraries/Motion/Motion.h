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

		Servo servoUltrasound;
		int pingPin;
		int ultraSoundServo;		                // Pin where the servo of the ultrasound sensor is connected
		int maxDistance = 20;                       // Distance detected where so stop driving
		int turnTime = 20;                         // Time to turn when detecting something
		int initialSetupUltrasoundServo = 100;      // Amount of time needed to return ultrasound servo to the initial position
		int servoLeftPin;		                    // Pin for left servo wheel
		int servoRightPin;      		            // Pin for right servo wheel
		int degreeRight = 20;	                    // Amount of degrees on the left side of the ultrasound sensor
		int degreeLeft = 110;                       // Amount of degrees on the right side of the ultrasound sensor
		int ultraServoDelay = 6;                    // Time the ultrasound servo needs to turn before meassuring can start again
		int servoGrabPin;
	public:
		Motion(int robot);
		void setup();
		String test();
		
		int measureUltrasound();
		float measurement();
		float microsecondsToCentimeters(float microseconds);
		void turnAfterObstacle(int angle);
		void startDriving();
		void stopDriving();
		void openGrabber();
		void closeGrabber();
		void grabObject();
		void dropObject();
		int leftWheelStatus;
		int rightWheelStatus;
		
		/*float startX;
		float startY;
		float distanceEncoder;*/
};

#endif