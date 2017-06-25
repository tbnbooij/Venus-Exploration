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
    
    
  if (lineDetection == 1 || lineDetection == 2 || lineDetection == 3){
    Serial.println(lineDetection);
      motion.stopDriving();
      motion.startDrivingBackwards();
      delay(200);
      motion.stopDriving();
      delay(10);

      if(lineDetection == 1) {
        motion.turnLeftCliff();
      }
      else {
        motion.turnRightCliff(); 
      }
      
  }
  else {
    motion.startDriving();
  }
  /*
  else{
  
      int turnOrNot = motion.measureUltrasound();
      if (turnOrNot < 0 && lineDetection == 0){
        motion.startDriving();   
      }
      else{
        
        motion.turnAfterObstacle(turnOrNot);
        
        }
  }*/
  

}

/*
 *   else if (lineDetection == 2){
      // Line on the right
      motion.stopDriving();
      motion.startDrivingBackwards();
      delay(100);
      motion.stopDriving();
      delay(10);
      motion.turnLeftCliff();
  }
  else if (lineDetection == 3){
      // Edge case: Line under left AND right
      motion.stopDriving();
      motion.startDrivingBackwards();
      delay(100);
      motion.stopDriving();
      delay(10);
      motion.turnRightCliff();
  }
  */

