#include <IR.h>
#include <Motion.h>
#include <Encoder.h>
#include <Math.h>

IR ir(1);
Motion motion(1);
Encoder encoder(1);
int t = 0;
  float anglereturn;
  int rockChannel;

void setup(){
  ir.setup();
  Serial.begin(9600);
  }
void loop(){
  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  switch(t) {
    case 0:
      rockChannel=ir.readRockSensor();
  
      if(rockChannel > 0) {
        t = 1;
        anglereturn=ir.findAngleRockRobot(rockChannel);
        anglereturn=(anglereturn/360)*2*M_PI;
        Serial.print("Angle: ");
        Serial.println(anglereturn);
      }
      break;

    case 1:
      if(encoder.checkAngleTurned(-1*anglereturn)) {
        motion.stopDriving();
        t = 2;
      } else {
        if(anglereturn<0){
          motion.turnLeft();
        }
        if(anglereturn>0){
          motion.turnRight();
        }
      }
      break;
  }

  Serial.print("Status: ");
  Serial.println(t);
}
