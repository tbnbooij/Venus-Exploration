#include <IR.h>
#include <Motion.h>
#include <Encoder.h>
#include <math.h>

IR ir(1);
Motion motion(1);
Encoder encoder(1);
int t = 0;
float anglereturn;
int rockChannel;

void setup() {
  ir.setup();
  encoder.setup();
  Serial.begin(9600);
}
void loop() {
  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  rockChannel = ir.readRockSensor();
    Serial.print("Channel found: ");
    Serial.println(rockChannel);

  if (rockChannel > 0) {
    motion.startDrivingBackwards();
    delay(50);
    motion.stopDriving();
    t = 1;
    anglereturn = ir.findAngleRockRobot(rockChannel);
    Serial.print("Angle (degree): ");
    Serial.println(anglereturn);
    if (anglereturn != 0.0f) {
      if (anglereturn < 0) {
        motion.turnLeft();
      }
      if (anglereturn > 0) {
        motion.turnRight();
      }
      delay(180 / 15.6 * abs(anglereturn));
      motion.stopDriving();
      delay(200);
    } else {
      motion.openGrabber();
      delay(100);
      motion.startDriving();
      delay(700);
      motion.stopDriving();
      delay(250);
      motion.closeGrabber();
      delay(200);
    }
  } else {
    motion.startDriving();
  }

  Serial.print("Status: ");
  Serial.println(t);


  Serial.println("----------");
}
