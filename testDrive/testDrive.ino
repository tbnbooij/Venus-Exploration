#include <Drive.h>

Drive drive(9,10,13,12);

void setup() {
  Serial.begin(9600);
  drive.setup();
}

void loop() {
  
  int obstacle = drive.measureUltrasound();
  if(obstacle == -1){  
    drive.startDriving();
  }
  else {drive.turnAfterObstacle(obstacle);}
}
