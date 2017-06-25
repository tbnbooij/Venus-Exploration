#include <Motion.h>
//#include <Encoder.h>

Motion motion(1);
//Encoder encoder(2);

int test = 1;
int angle_begin = 0;

int sensorPinline1 = A4;
int sensorPinline2 = A1;
int threshold = 180;
int thing; 
int line = 0;


void setup() {
  Serial.begin(9600);
  motion.setup();
 // encoder.setup();
  
  pinMode(sensorPinline1, INPUT);
  pinMode(sensorPinline2, INPUT);
}

void loop() {
  /*int turnOrNot = motion.measureUltrasound();
  if (turnOrNot < 0 && line == 0){
    motion.startDriving();   
  }
  else{
    
    motion.turnAfterObstacle(turnOrNot);
    
    }*/


  int Stateleft = analogRead(sensorPinline1);
  int Stateright = analogRead(sensorPinline2);
    
  //Serial.println(Stateright);
          
  // left sensor sees tape
  if (Stateleft<threshold && Stateright>threshold){
    thing = 1;
  }
  //right sensor sees tape
  if (Stateright<threshold && Stateleft>threshold){
    thing = 2;
  }
  //bot see tape
  if(Stateright<threshold && Stateleft<threshold){
    thing = 3;
  }
  //no sensor sees tape
  if (Stateleft>threshold && Stateright>threshold){
    thing = 0;
  }
//    Serial.println(thing); 

    if (thing == 1){
      line = 1;
      motion.stopDriving();
      motion.turnLeft();
      delay(100);
    }
    else if (thing == 2){
            motion.stopDriving();
            line = 1;

      motion.turnRight();
      delay(100);
    }
    else if (thing == 0){
      line = 0;
      motion.startDriving();
      }
    Serial.println(Stateleft);
    

  
  
 /* encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  int wall;
  if(test == 1) {
    wall = motion.positionWall();
  }*/
  
  /*if(wall > -1) {
    if(test == 1) {
      angle_begin = encoder.getRawAngle();
      Serial.println("wall: "  + wall);
      test = 0;
    }
    if(wall > 75) {
      wall = abs(wall - 75);
      //motion.turnLeft();
      //if(encoder.checkAngleTurned(angle_begin, wall, true)) {
      //  motion.stopDriving();
      //}
    } else {
      wall = abs(wall-75);
      //motion.turnRight();
      //if(encoder.checkAngleTurned(angle_begin, wall, false)) {
      //  motion.stopDriving();
      //}        
    }
  }*/
  
  
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
}
