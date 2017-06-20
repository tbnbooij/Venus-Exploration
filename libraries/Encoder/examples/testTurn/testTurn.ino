#include <Encoder.h>
#include <Motion.h>
const int robot = 1;

int state;
int state2;

float angle_start;

Encoder encoder(robot);
Motion motion(robot);

int d = 360;


int i = 0;

void setup() {
  Serial.begin(9600);
  motion.setup();
  encoder.setup();

  delay(500);
   motion.closeGrabber();
   angle_start = 0;
   motion.turnLeft();
}

void loop() {
  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  if(encoder.checkAngleTurned(d*M_PI*2/360)) {
    motion.stopDriving();
  } else {
    Serial.print("x: ");
    Serial.print(encoder.getX());
    Serial.print("; y: ");
    Serial.print(encoder.getY());
    Serial.print("; angle: ");
    Serial.println(encoder.getAngle());
  }
}
