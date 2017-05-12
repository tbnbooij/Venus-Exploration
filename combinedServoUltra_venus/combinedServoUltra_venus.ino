
#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

boolean isDriving = false;
float distance = 0;

Servo servoUltrasound;
int pingPin = 9;
int ultraSoundServo = 10;                   // Pin where the servo of the ultrasound sensor is connected
int maxDistance = 20;                       // Distance detected where so stop driving
int turnTime = 200;                         // Time to turn when detecting something
int initialSetupUltrasoundServo = 100;      // Amount of time needed to return ultrasound servo to the initial position
int servoLeftPin = 13;                      // Pin for left servo wheel
int servoRightPin = 12;                     // Pin for right servo wheel
int degreeRight = 20;                       // Amount of degrees on the left side of the ultrasound sensor
int degreeLeft = 110;                       // Amount of degrees on the right side of the ultrasound sensor

void setup() {
  Serial.begin(9600);
    servoUltrasound.attach(ultraSoundServo);
    servoUltrasound.write(50);
    delay(initialSetupUltrasoundServo);
    
}

void loop() {
  
  boolean drive = meassureUltrasound();
  if(drive == true){  
    // Full speed forward
    servoLeft.attach(servoLeftPin);                     
    servoRight.attach(servoRightPin); 
    servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
    servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  }
  else {turnAfterObstacle();}
  
} 

boolean meassureUltrasound(){
  
    for (int i=degreeRight; i<degreeLeft; i=i+1){    
    servoUltrasound.attach(ultraSoundServo);
    servoUltrasound.write(i);
    delay(7);

    // Make something that turns right after detecting on the left and vice versa!!
      if(meassurement()< maxDistance){
        return false;
      }
    }
    return true;
}


float meassurement(){  
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

float microsecondsToCentimeters(float microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void turnAfterObstacle(){
    servoLeft.attach(servoLeftPin);                     
    servoRight.attach(servoRightPin); 
    servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
    servoRight.writeMicroseconds(1700);
    delay(turnTime);
    servoLeft.detach();
    servoRight.detach(); 
}

void stopDriving(){
    servoLeft.detach();
    servoRight.detach(); 
}
