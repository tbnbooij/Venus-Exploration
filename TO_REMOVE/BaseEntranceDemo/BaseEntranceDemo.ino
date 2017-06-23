#include <IR.h>
#include <Motion.h>
#include <Encoder.h>
#include <math.h>
#include <Beacon.h>

IR ir(1);
Motion motion(1);
Encoder encoder(1);
int ldr = A2;
Beacon beacon(ldr);
int t = 0;
float anglereturn;
int rockChannel;

void setup() {
  ir.setup();
  motion.setup();
  beacon.start();
  Serial.begin(9600);
}

bool detectedWall = false;

void loop() {

  if (!detectedWall) {
    motion.startDriving();
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
        delay(700);
        motion.stopDriving();
        motion.turnLeft();
        delay(110);
        motion.stopDriving();
        motion.startDriving();
        break;
      case 2:
        // Idem, right hand side
        Serial.println("Found rock on right side");
        motion.startDrivingBackwards();
        delay(700);
        motion.stopDriving();
        motion.turnRight();
        delay(110);
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
        delay(1000);
        motion.stopDriving();
        detectedWall = true;

        // Throw away "old sweep"
        short bMeas = beacon.measure(motion.ultrasoundAngle, motion.degreeLeft, motion.degreeRight, motion.servoUltrasound);

        while (bMeas == -1) {
          motion.turnHead();
          bMeas = beacon.measure(motion.ultrasoundAngle, motion.degreeLeft, motion.degreeRight, motion.servoUltrasound);

        }
        bMeas = -1;

        // Do a "NEW" sweep
        while (bMeas == -1) {
          motion.measureUltrasound();
          bMeas = beacon.measure(motion.ultrasoundAngle, motion.degreeLeft, motion.degreeRight, motion.servoUltrasound);
        }

        boolean leftSide = bMeas > motion.normal;

        if (leftSide) {
          motion.turnRight();
        } else {
          motion.turnLeft();
        }
        delay(740);
        motion.stopDriving();
        delay(600);
        motion.startDriving();
        delay(5000);
        motion.stopDriving();
        delay(600);
        if (leftSide) {
          motion.turnLeft();
        } else {
          motion.turnRight();
        }
        delay(690);
        motion.stopDriving();
        delay(600);
        motion.startDriving();
        delay(3000);
        motion.stopDriving();
        delay(600);
        if (leftSide) {
          motion.turnLeft();
        } else {
          motion.turnRight();
        }
        delay(680);
        motion.stopDriving();
        delay(400);
        motion.startDriving();
        /**
           IN FRONT OF ENTRANCE
        */
        motion.servoUltrasound.write(motion.normal);
        boolean measureLine = false;
        while (true) {
          int alignBase = ir.alignWithBase();
          if (alignBase == 1) {
            motion.stopDriving();
            delay(50);
            motion.startDrivingBackwards();
            delay(100);
            motion.stopDriving();
            delay(400);
            motion.turnRight();
            delay(50);
            motion.stopDriving();
            delay(200);
            motion.startDriving();
          }
          else if (alignBase == 2) {
            motion.stopDriving();
            delay(50);
            motion.startDrivingBackwards();
            delay(100);
            motion.stopDriving();
            delay(200);
            motion.turnLeft();
            delay(50);
            motion.startDriving();
          }

          measureLine = ir.readRawLineSensor() > 190;

          if (!measureLine) {
            continue;
          }
          int dist = motion.measurement();
          Serial.print("Dist: ");
          Serial.println(dist);
          if (dist <= 20.0f && dist >= 0.0f) {
            Serial.println("STOP Ultrasound");
            motion.stopDriving();
            break;
          }
        };
    }
  }
}


