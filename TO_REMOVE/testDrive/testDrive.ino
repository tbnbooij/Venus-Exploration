#include <Motion.h>
#include <Encoder.h>

Motion motion(2);
//Encoder encoder(2);

int test = 1;


void setup() {
  Serial.begin(9600);
  motion.setup();
}

void loop() {    
   /*while(test == 1){ 
    motion.closeGrabber();
    delay(1000);
    motion.startDriving();
    delay(300);
    motion.stopDriving();
    delay(1000);
    motion.openGrabber();
    delay(1000);
    motion.startDriving();
    delay(300);
    motion.stopDriving();
    delay(1000);
    motion.closeGrabber();
    delay(1000);
    motion.startDriving();
    delay(1000);
    motion.stopDriving();
    delay(1000);
    motion.openGrabber();
    test=0;
   }*/

  /*float x = encoder.getX();
  float y = encoder.getY();
  float distance = 0.10 
  motion.startDriving(x, y, distance);

  if( encoder.checkDistanceDriven(motion.startX, motion.startY, motion.distance ) {
    motion.stopDriving();
    motion.closeGrabber();
    delay(2000);
  }*/


 
  int obstacle = motion.measureUltrasound();
  if(obstacle == -1){  
    motion.startDriving();
  }
  else {motion.turnAfterObstacle(obstacle);}
}
