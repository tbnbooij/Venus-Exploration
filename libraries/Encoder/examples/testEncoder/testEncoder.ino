#include <Motion.h>
#include <Encoder.h>

const int robot = 1;

Encoder encoder(robot);
Motion motion(robot);

void setup() {
  Serial.begin(9600);
  
  motion.setup();
  encoder.setup();

  motion.startDriving();
}

void loop() {
  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
}
