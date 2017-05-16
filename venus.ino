#include <Encoder.h>

Encoder encoder(7,8);
//Encoder encoder(D6, D6);

void setup() {
	Serial.begin(9600);
}

void loop() {
	float reading[2];
	encoder.readEncoder(reading);
	encoder.updateRelativePosition(reading);
	encoder.checkDistanceDriven(0, 0, 0);

	Serial.print("reading: ");
	Serial.println(reading[0]);
}
