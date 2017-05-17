#ifndef Drive_h
#define Drive_h

#include "Arduino.h"
#include "Servo.h"

class Drive
{
	private:
		Servo servoLeft;                             // Declare left and right servos
		Servo servoRight;

		boolean isDriving = false;
		float distance = 0;

		Servo servoUltrasound;
		int pingPin;
		int ultraSoundServo;		                // Pin where the servo of the ultrasound sensor is connected
		int maxDistance = 20;                       // Distance detected where so stop driving
		int turnTime = 200;                         // Time to turn when detecting something
		int initialSetupUltrasoundServo = 100;      // Amount of time needed to return ultrasound servo to the initial position
		int servoLeftPin;		                    // Pin for left servo wheel
		int servoRightPin;      		            // Pin for right servo wheel
		int degreeRight = 20;	                    // Amount of degrees on the left side of the ultrasound sensor
		int degreeLeft = 110;                       // Amount of degrees on the right side of the ultrasound sensor
	public:
		Drive(int a, int b, int c, int d);
		void setup();
		String test();
		
		boolean measureUltrasound();
		float measurement();
		float microsecondsToCentimeters(float microseconds);
		void turnAfterObstacle();
		void startDriving();
		void stopDriving();
};

#endif
