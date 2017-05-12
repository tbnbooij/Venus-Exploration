
#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

boolean isDriving = false;
float distance = 0;

Servo servoUltrasound;
int pingPin = 9;


void setup() {
  Serial.begin(9600);
    servoUltrasound.attach(10);
    servoUltrasound.write(50);
    delay(100);
    
}

void loop() {
  
  boolean drive = meassureUltrasound();
  if(drive == true){  
    // Full speed forward
    servoLeft.attach(13);                      // Attach left signal to pin 13
    servoRight.attach(12); 
    servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
    servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  }
  else {

    servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
    servoRight.writeMicroseconds(1700);
    delay(400); 
  }
  
} 

boolean meassureUltrasound(){
  
    for (int i=50; i<100; i=i+1){    
    servoUltrasound.attach(10);
    servoUltrasound.write(i);
    delay(7);
      if(meassurement()<20){
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
