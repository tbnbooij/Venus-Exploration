#include <Motion.h>

Motion motion(2);


void setup() {
  Serial.begin(9600);
  motion.setup();
}

void loop() {

  motion.openGrabber();
  delay(1000);
  motion.closeGrabber();
  delay(2000);
  
  /*int obstacle = motion.measureUltrasound();
  if(obstacle == -1){  
    motion.startDriving();
  }
  else {motion.turnAfterObstacle(obstacle);}*/
}
