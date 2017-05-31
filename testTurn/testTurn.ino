#include <Encoder.h>
#include <Motion.h>
const int robot = 2;

int state;
int state2;

float angle_start;

Encoder encoder(robot);
Motion motion(robot);

int i = 0;

void setup() {
  Serial.begin(9600);
  motion.setup();
  encoder.setup();

  delay(500);
   angle_start = 0;
   motion.turnRight();
}

void loop() {
  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  if(encoder.checkAngleTurned(angle_start, 2*M_PI, false)) { // last argument is true when turning left and false when turning right
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
