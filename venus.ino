#include <Encoder.h>

Encoder encoder(7,8);

void setup() {
	Serial.begin(9600);
}

void loop() {
	Serial.println("Encoder library: " + encoder.test());
  Serial.println("Drive library: " + drive.test());
}
