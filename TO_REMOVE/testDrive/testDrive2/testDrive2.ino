#include <Motion.h>
//#include <Encoder.h>
#include <IR.h>

Motion motion(1);
//Encoder encoder(2);
IR ir(1);

void setup() {
  // put your setup code here, to run once:
  motion.setup();
  ir.setup();
  Serial.begin(9600);

}

void loop() {


  int lineDetection = ir.readLineSensor();

  if (lineDetection == 2){
      motion.stopDriving();
      motion.turnRightCliff();
  }
  else if (lineDetection == 1){
      motion.stopDriving();
      motion.turnLeftCliff();
  }
  else if (lineDetection == 3){
      motion.stopDriving();
      motion.turnRightCliff();
  }
  else{
  
      int turnOrNot = motion.measureUltrasound();
      if (turnOrNot < 0 && lineDetection == 0){
        motion.startDriving();   
      }
      else{
        
        motion.turnAfterObstacle(turnOrNot);
        
        }
  }

}
