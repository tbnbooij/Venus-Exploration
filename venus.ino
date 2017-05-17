#include <Encoder.h>

Encoder encoder(7,8);

void setup() {
	Serial.begin(9600);
}

void loop() {
	float reading[2];
	encoder.readEncoder(reading);
	encoder.updateRelativePosition(reading);
	//encoder.checkDistanceDriven(0, 0, 0);
}
