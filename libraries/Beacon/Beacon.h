#ifndef Beacon_h
#define Beacon_h

#include "Arduino.h"
#include "Servo.h"

class Beacon
{
	private:
    int angle;
    int normal;
    int USServo;
    int intDelay;
    Servo s;
	public:
    Beacon(int _normal, int _angle);
    int sweep();
};

#endif
