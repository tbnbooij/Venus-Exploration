#include <Encoder.h> 
#include <Motion.h> 
#include <Wireless.h> 
#include <IR.h>

const int robot = 1;

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
  // put your main code here, to run repeatedly:

}
