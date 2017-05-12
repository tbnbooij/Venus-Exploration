#include <Servo.h>   
Servo servoUltrasound;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  servoUltrasound.attach(10);
  servoUltrasound.write(0);
  delay(1000);
  for (int i=0; i<175; i=i+1){
  servoUltrasound.attach(10);
  servoUltrasound.write(i);
  delay(10);
  }
  
 
}
