#include <Motion.h>
#include <Encoder.h>
#include<math.h>

Encoder encoder(1);
Motion motion(1);
int situation = 0;
float distance = 0;
float angle = 0;
void setup()
{
  motion.setup();
  encoder.setup();
  Serial.begin(9600);
}

void loop()
{
  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  switch (situation)
  {
    case 0:
      motion.startDriving();
      if (encoder.checkDistanceDriven(0.5)) {
        situation = 1;
        motion.stopDriving();
      }
      break;
    case 1:
      motion.turnLeft();
      if (encoder.checkAngleTurned(90*2*M_PI/360)) {
        situation = 2;
        motion.stopDriving();
      }
      break;
    case 2:
      motion.startDriving();
      if (encoder.checkDistanceDriven(0.3)) {
        situation = 3;
        motion.stopDriving();
      }
      break;
    case 3:
      motion.turnRight();
      if (encoder.checkAngleTurned(-20 * 2 * M_PI / 360)) {
        situation = 4;
        motion.stopDriving();
      }
      break;
    case 4:
      motion.startDriving();
      if (encoder.checkDistanceDriven(0.3)) {
        situation = 5;
        motion.stopDriving();
      }
      break;
    case 5:
      delay(2000);
      angle = encoder.getTurnAngle();
      distance = sqrt(pow(encoder.getX(), 2) + pow(encoder.getY(), 2));
      if (angle > 0) {
        motion.turnLeft();
      }
      if (angle < 0) {
        motion.turnRight();
      }
      situation = 6;
      break;
    case 6:
      if (encoder.checkAngleTurned(angle)) {
        situation = 7;
        motion.stopDriving();
      }
      break;
    case 7:
      motion.startDriving();
      if (encoder.checkDistanceDriven(distance)) {
        situation = 8; // does not exist
        motion.stopDriving();
      }
      break;
  }
}
