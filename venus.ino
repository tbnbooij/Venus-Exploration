#include <Encoder.h>
#include <Motion.h>
const int robot = 1;


Encoder encoder(robot);
Motion motion(robot);

int i = 0;

void setup() {
	Serial.begin(9600);
	motion.setup();
  encoder.setup();

  motion.startDriving();
}

void loop() {
  encoder.updateRelativePosition(motion.leftWheelStatus, motion.rightWheelStatus);
  if(encoder.checkDistanceDriven(0, 0, 1)) {
    motion.stopDriving();
  } else {
    Serial.print("x: ");
    Serial.print(encoder.getX());
    Serial.print("; y: ");
    Serial.print(encoder.getY());
    Serial.print("; angle: ");
    Serial.println(encoder.getAngle());
  }
}
