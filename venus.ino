/*
   0: searching rocks
   1: found a rock
   2: return to base (not turned)
   3: return to base (turned towards base w/ relative position)
   4: return to base (found beacon), finding entrance
   5: on the ramp
*/


#include <Encoder.h>
#include <Motion.h>
//#include <Wireless.h>
#include <IR.h>

const int robot = 1;

boolean returningToBase = false;



boolean cliffSideHillDetection = false;
boolean cliffSideHillDetectionPrevious = false;

boolean avoidingObstacle = false;

Encoder encoder(robot);
Motion motion(robot);
//Wireless wireless(robot);
//Beacon beacon;
IR ir(robot);

void setup() {
  Serial.begin(9600);
  motion.setup();
  encoder.setup();
  //wireless.setup();
  ir.setup();
}

void loop() {
  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);

  cliffSideHillDetection = false;
  int ultrasoundAngle = motion.measureUltrasound();
  if (ultrasoundAngle == -1) {
    if (ultrasoundAngle > motion.normal ) {
      motion.turnRight();
    }
    if (ultrasoundAngle <= motion.normal ) {
      motion.turnLeft();
    }
  } else {
    cliffSideHillDetection = true;
  }

  int lineState = ir.readLineSensor();
  if (lineState > 0) {
    cliffSideHillDetection = true;
    if (lineState == 1 || lineState == 3) {
      motion.turnRight();
    }
    if (lineState == 2) {
      motion.turnLeft();
    }
  }

  if (cliffSideHillDetection == false && cliffSideHillDetectionPrevious == true) {
    if (returningToBase == true) {
      motion.startDriving();
      avoidingObstacle = true;
    } else {
      motion.stopDriving();
    }
  }

  int rockChannel = ir.readRockSensor();
  if (rockChannel > 0) {
    motion.startDrivingBackwards();
    delay2(50);
    motion.stopDriving();
    float anglereturn = ir.findAngleRockRobot(rockChannel);
    if (returningToBase == false) {
      if (anglereturn != 0.0f) {
        if (anglereturn < 0.0f) {
          motion.turnLeft();
        }

        if (anglereturn > 0.0f) {
          motion.turnRight();
        }

        delay2(180 / 15.6 * abs(anglereturn));
        motion.stopDriving();
        delay2(200);
      } else {
        motion.openGrabber();
        delay2(100);
        motion.startDriving();
        delay2(700);
        motion.stopDriving();
        delay2(250);
        motion.closeGrabber();
        delay2(200);
        returningToBase = true;
      }
    } else { // cant pick up the rock, it is already returning to base
      /**
         @TODO: avoid the rock! Check how much turning is enough per channel to avoid it entirely
      */
    }
  } else {
    // No rock detected
    if (returningToBase) {
      int turnAngle = encoder.getTurnAngle();
      if (turnAngle > 0) {
        motion.turnLeft();
      }

      if (turnAngle < 0) {
        motion.turnRight();
      }
    } else {
      motion.startDriving();
    }
  }

  if (avoidingObstacle == true) {
    if (encoder.checkDistanceDriven(0.4)) {
      motion.stopDriving();
      avoidingObstacle = false;
    }
  }

  cliffSideHillDetectionPrevious = cliffSideHillDetection;
}

/**
   Function to delay a certain time, but without 'forgetting' to update the relative position.
*/
void delay2(int t) {
  for (int i = 0; i < t; i += 5) {
    delayMicroseconds(5000);
    encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  }
}

