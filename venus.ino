/*
 * 0: searching rocks
 * 1: found a rock
 * 2: return to base (not turned)
 * 3: return to base (turned towards base w/ relative position)
 * 4: return to base (found beacon), finding entrance
 * 5: on the ramp
 */


#include <Encoder.h> 
#include <Motion.h> 
//#include <Wireless.h> 
#include <IR.h>

const int robot = 1;
int robotStatus = 0;

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

  if(robotStatus == 2) {
    // turn towards lab
    float angle = encoder.getAngle();

    // turn towards lab
    float encoderAngle = encoder.getAngle();
    float requiredAngle = encoder.boundAngle(M_PI - atan(encoder.getY() / encoder.getX()));

    float turnAngle = encoder.boundAngle(2*M_PI - requiredAngle - encoderAngle);
    
    if(turnAngle > 0) {
      motion.turnLeft();
    } else {
      motion.turnRight();
    }
    
    if(encoder.checkAngleTurned(turnAngle)) {
      motion.startDriving(); // start driving forward after the turning has been completed
      robotStatus = 3;
    }
  }

  if(robotStatus == 3) {
    if( detectHillAndTurn() ) {
      // Find beacon
    }
    
  }

//  switch(robotStatus) {
//    case 0: case 2: case 3:
//      
//      break;
//  }
  
}

boolean detectHillAndTurn() {
  int ultrasoundAngle = motion.measureUltrasound(); // 'head' servo will turn from left to right with this
  if(ultrasoundAngle == -1) {
    // no object is close enough
    motion.startDriving();
    return true;
  } else {
    // there is something in the way, turn away from it
    motion.turnAfterObstacle(ultrasoundAngle);
    if(robotStatus == 3) {
      robotStatus = 2;
    }
    return false;
  }
}

