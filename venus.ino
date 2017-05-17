#include <Encoder.h>
#include <Drive.h>

Encoder encoder(7,8);
Drive drive(9, 10, 13, 12);

void setup() {
	Serial.begin(9600);
  drive.setup();
}

void loop() {
	Serial.println("Encoder library: " + encoder.test());
  Serial.println("Drive library: " + drive.test());

  if(drive.measureUltrasound()) {
    drive.startDriving();
  }
}
