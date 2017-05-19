#include <Encoder.h>
#include <Motion.h>

Encoder encoder(1);
Motion motion(1);

int i = 0;

void setup() {
	Serial.begin(9600);
	motion.setup();
}

void loop() {
  if(i > 1000) {
    motion.stopDriving();
  } else {
    motion.startDriving();
  }
  float reading[2];
  encoder.readEncoder(reading);
  
  Serial.print("reading[0]: ");
  Serial.print(reading[0]);
  Serial.print("; reading[1]: ");
  Serial.println(reading[1]);
  i++;
}
