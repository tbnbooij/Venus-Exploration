#include "Drive.h"
#include "Arduino.h"
#include "Servo.h"

Drive::Drive(int a, int b, int c, int d) {
	pingPin = a;
	ultraSoundServo = b;
	servoLeftPin = c;
	servoRightPin = d;
}

void Drive::setup() {
	servoUltrasound.attach(ultraSoundServo);
    servoUltrasound.write(50);
    delay(initialSetupUltrasoundServo);
}


String Drive::test() {
	return "1";
}

boolean Drive::measureUltrasound(){
  
    for (int i=degreeRight; i<degreeLeft; i=i+1){    
    servoUltrasound.attach(ultraSoundServo);
    servoUltrasound.write(i);
    delay(7);

    // Make something that turns right after detecting on the left and vice versa!!
      if(measurement()< maxDistance){
        return false;
      }
    }
    return true;
}


float Drive::measurement(){  
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

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  
  
}

float Drive::microsecondsToCentimeters(float microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void Drive::turnAfterObstacle(){
    servoLeft.attach(servoLeftPin);                     
    servoRight.attach(servoRightPin); 
    servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
    servoRight.writeMicroseconds(1700);
    delay(turnTime);
    servoLeft.detach();
    servoRight.detach(); 
}

void Drive::startDriving() {
	servoLeft.attach(servoLeftPin);                     
    servoRight.attach(servoRightPin); 
    servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
    servoRight.writeMicroseconds(1300);        // Right wheel clockwise
}

void Drive::stopDriving(){
    servoLeft.detach();
    servoRight.detach(); 
}
