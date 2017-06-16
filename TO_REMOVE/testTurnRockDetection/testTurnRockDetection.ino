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
void loop(){
  
  /*encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  switch(t) {
    case 0:
      rockChannel=ir.readRockSensor();
      Serial.print("Channel found: ");
      Serial.println(rockChannel);
  
      if(rockChannel > 0) {
        t = 1;
        anglereturn=-1*ir.findAngleRockRobot(rockChannel);
        Serial.print("Angle (degree): ");
        Serial.println(anglereturn);
        anglereturn=(anglereturn/360)*2*M_PI;
        if(anglereturn>0){
          motion.turnLeft();
        }
        if(anglereturn<0){
          motion.turnRight();
        }
      }
      break;

    case 1:
      if(encoder.checkAngleTurned(anglereturn)) {
        motion.stopDriving();
        t = 2;
      }
      break;
  }

  Serial.print("Status: ");
  Serial.println(t);*/

        rockChannel=ir.readRockSensor();

    
  Serial.println("----------");
  delay(1000);

}
