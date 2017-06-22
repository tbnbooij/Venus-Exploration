#include <Encoder.h>
#include <Motion.h>
//#include <Wireless.h>
#include <IR.h>
#include <Beacon.h>

const int robot = 1;

boolean returningToBase = false;
boolean beaconFound = false;

float turnBaseAngle = 0.0f;

boolean cliffSideHillDetection = false;
boolean cliffSideHillDetectionPrevious = false;

boolean avoidingObstacle = false;

Encoder encoder(robot);
Motion motion(robot);
//Wireless wireless(robot);
Beacon beacon(A2);
IR ir(robot);

void setup() {
  Serial.begin(9600);
  motion.setup();
  encoder.setup();
  //wireless.setup();
  ir.setup();
  beacon.start();
}

void loop() {
  Serial.println("------");

  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);

  cliffSideHillDetectionPrevious = cliffSideHillDetection;
  cliffSideHillDetection = false;
  int ultrasoundAngle = motion.measureUltrasound();
  if (ultrasoundAngle != -1) {
    Serial.println("ULTRASOUND");
    if (ultrasoundAngle > motion.normal ) {
      motion.turnRight();
    }
    if (ultrasoundAngle <= motion.normal ) {
      motion.turnLeft();
    }
    cliffSideHillDetection = true;
  }

  int lineState = 0; //ir.readLineSensor();
  if (lineState > 0) {
    Serial.print("Line detected: ");

    cliffSideHillDetection = true;
    if (lineState == 1) {
      motion.turnRight();
      Serial.println("left side");
    }
    if (lineState == 2) {
      motion.turnLeft();
      Serial.println("right side");
    }
    if (lineState == 3) {
      motion.turnRight();
      Serial.println("both sides");
    }
  }

  if (!cliffSideHillDetection && cliffSideHillDetectionPrevious) {
    Serial.println("No cliff/side/hill anymore");
    if (returningToBase) {
      motion.startDriving();
      avoidingObstacle = true;
    } else {
      motion.stopDriving();
    }
  }

  if (cliffSideHillDetection) {
    return;
  }

  int rockChannel = ir.readRockSensor();
  if (rockChannel > 0) {
    Serial.print("Rock found: ");
    Serial.println(rockChannel);
    motion.startDrivingBackwards();
    delay2(50);
    motion.stopDriving();
    float anglereturn = ir.findAngleRockRobot(rockChannel);
    if (!returningToBase) {
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
      // detect the beacon
      int beaconMeasurement = beacon.measure(motion.ultrasoundAngle, motion.degreeLeft, motion.degreeRight, motion.servoUltrasound);

      if (beaconMeasurement != -1) {
        // beacon not detected
        if (turnBaseAngle == 0) {
          turnBaseAngle = encoder.getTurnAngle();
          if (turnBaseAngle > 0) {
            motion.turnLeft();
          }

          if (turnBaseAngle < 0) {
            motion.turnRight();
          }
        }
      } else {
        // found the beacon
        Serial.println("Beacon found");
        beaconFound = true;
        turnBaseAngle = 2 * M_PI / 360 * (beaconMeasurement - motion.normal);

        if (turnBaseAngle > 1) {
          motion.turnLeft();
        }

        if (turnBaseAngle < -1) {
          motion.turnRight();
        }
      }
    } else {
      motion.startDriving();
    }
  }

  if (avoidingObstacle) {
    if (encoder.checkDistanceDriven(0.4)) {
      motion.stopDriving();
      avoidingObstacle = false;
    }
  }

  if (turnBaseAngle > 0.0f) {
    if (encoder.checkAngleTurned(turnBaseAngle)) {
      turnBaseAngle = 0.0f;
      motion.stopDriving();
      delay2(500);
      motion.startDriving();
    }
  }

  if (beaconFound && turnBaseAngle == 0) {
    /**
      @TODO Base entering
    */
  }
}

/**
  Function to delay a certain time, but without 'forgetting' to update the relative position.
*/
void delay2(int t) {
  for (int i = 0; i < t; i++) {
    delayMicroseconds(1000);
    encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  }
}

