#include <Encoder.h>
#include <Drive.h>

Encoder encoder(1);
Drive drive(9, 10, 13, 12);

int i = 0;

void setup() {
	Serial.begin(9600);
  drive.setup();
}

void loop() {
  if(i > 1000) {
    drive.stopDriving();
  } else {
    drive.startDriving();
  }
  float reading[2];
  encoder.readEncoder(reading);
  
  Serial.print("reading[0]: ");
  Serial.print(reading[0]);
  Serial.print("; reading[1]: ");
  Serial.println(reading[1]);
  i++;
}
