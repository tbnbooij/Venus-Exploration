#include <IR.h>

const int robot = 1;

IR ir(robot);

void setup() {
  // put your setup code here, to run once:
  ir.setup();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lineDetection = ir.readLineSensor();

  Serial.println(lineDetection);
}
