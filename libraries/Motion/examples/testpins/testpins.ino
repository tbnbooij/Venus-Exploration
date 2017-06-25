#include <Servo.h>

Servo test;
int testpin = 9;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  test.attach(testpin);
  test.writeMicroseconds(1700);
  delay(1000);
}
