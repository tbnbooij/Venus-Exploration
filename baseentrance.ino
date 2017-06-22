#include <IR.h>
#include <Motion.h>
#include <Encoder.h>
#include <math.h>
#include <Beacon.h>

IR ir(1);
Motion motion(1);
Encoder encoder(1);
Beacon beacon(A2);
int t = 0;
float anglereturn;
int rockChannel;

void setup() {
  ir.setup();
  encoder.setup();
  beacon.start();
  Serial.begin(9600);
}

void loop() {
  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);

  if(true /* Should be edited later @TODO */) {
    switch (ir.alignWithBase()) {
      case 0:
        // Keep driving forward
        Serial.println("Keep driving forward");
        break;
      case 1:
        // Found rock on left hand side
        // Move backwards and turn left until alignment completes
        Serial.println("Found rock on left side");
        motion.startDrivingBackwards();
        delay2(500);
        motion.stopDriving();
        motion.turnLeft();
        delay2(150);
        motion.stopDriving();
        motion.startDriving();
        break;
      case 2:
        // Idem, right hand side
        Serial.println("Found rock on right side");
        motion.startDrivingBackwards();
        delay2(500);
        motion.stopDriving();
        motion.turnRight();
        delay2(150);
        motion.stopDriving();
        motion.startDriving();
        break;
      case 3:
        Serial.println("PERPENDICULAR");
        // Perpendicular
        // 1. Drive backwards
        // 2. Turn 90 degrees
        // 3. Move forward
        motion.startDrivingBackwards();
        delay2(1000);
        motion.stopDriving();

        // Throw away "old sweep"
        short bMeas = beacon.measure(motion.ultrasoundAngle, motion.degreeLeft, motion.degreeRight, motion.servoUltrasound);
        while(bMeas == -1) {
          motion.measureUltrasound();
          bMeas = beacon.measure(motion.ultrasoundAngle, motion.degreeLeft, motion.degreeRight, motion.servoUltrasound);
        }
        bMeas = -1;

        // Do a "NEW" sweep
        while(bMeas == -1) {
          motion.measureUltrasound();
          bMeas = beacon.measure(motion.ultrasoundAngle, motion.degreeLeft, motion.degreeRight, motion.servoUltrasound);
        }

        if(bMeas > motion.normal) {
          // Beacon to the left
          motion.turnRight();
          delay(180 / 15.6 * 90);
          motion.stopDriving();

        }
        else {
          // Beacon to the right
          motion.turnLeft();
          delay(180 / 15.6 * 90);
          motion.stopDriving();
        }
    };
  }
}

void delay2(int t) {
  for (int i = 0; i < t; i++) {
    delayMicroseconds(1000);
    encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  }
}
