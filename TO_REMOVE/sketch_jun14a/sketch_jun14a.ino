#include <Motion.h>
Motion motion(1);
void setup() {
  // put your setup code here, to run once:
  motion.setup();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  motion.measureUltrasound();

  Serial.println("---");
}
