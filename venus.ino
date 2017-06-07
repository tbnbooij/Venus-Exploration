/*0: searching rocks
1: found a rock
2: return to base (not turned)
3: return to base (turned towards base w/ relative position)
4: return to base (found beacon), finding entrance
5: on the ramp*/


#include <Encoder.h> 
#include <Motion.h> 
#include <Wireless.h> 
#include <IR.h>

const int robot = 1;
int robotStatus = 0;

Encoder encoder(robot); 
Motion motion(robot); 
Wireless wireless(robot); 
Beacon beacon(); 
IR ir();

void setup() {
  Serial.begin(9600); 
  motion.setup(); 
  encoder.setup(); 
  wireless.setup(); 
  ir.setup(); 

}

void loop() {
  encoder.updateRelativePosition();
  int ultrasoundAngle = motion.measureUltrasound();
  switch(robotStatus){
    case 0:
    case 2:
    case 3:
      if(ultrasoundAngle == -1){
        motion.startDriving();  
      }
      else {
        motion.turnAfterObstacle(utrasoundAngle);
      }
  }
}
