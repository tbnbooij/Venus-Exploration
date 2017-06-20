#include <Motion.h>
#inlude <Encoder.h>

Encoder encoder(1);
Motion motion(1);

int situation = 0;
float distance = 0;

void setup() {
  motion.setup();
  encoder.setup();
}

void loop() {
  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  switch(situation) {
    case 0:
      motion.startDriving();
      if(encoder.checkDistanceDriven(1.0)) {
        situation = 1;
        motion.stopDriving();
      }
      break;
    case 1:
      motion.turnLeft();
      if(encoder.checkAngleTurned(20)) {
        situation = 2;
        motion.stopDriving();
      }
      break;
    case 2:
      motion.startDriving();
      if(encoder.checkDistanceDriven(1.0)) {
        situation = 3;
        motion.stopDriving();
      }
      break;
    case 3:
      motion.turnRight();
      if(encoder.checkAngleTurned(-20)) {
        situation = 4;
        motion.stopDriving();
      }
      break;
    case 4:
      motion.startDriving();
      if(encoder.checkDistanceDriven(0.5)) {
        situation = 5;
        motion.stopDriving();
      }
      break;
    case 5:
      float angle = encoder.getTurnAngle();
      distance = sqrt(pow(encoder.getX(), 2) + pow(encoder.getY(), 2));
      if(angle > 2) {
        motion.turnLeft();
      }

      if(angle < -2) {
        motion.turnRight();
      }

      if(encoder.checkAngleTurned(angle)){
        situation = 6;
        motion.stopDriving();
      }
      break;
    case 6:
      motion.startDriving();
      if(encoder.checkDistanceDriven(distance)) {
        situation = 7; // does not exist
        motion.stopDriving();
      }
      break;
  }
}
