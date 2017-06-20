#include "Beacon.h"
#include "Arduino.h"
#include "Servo.h"

Beacon::Beacon(uint8_t pin) {
  LDRPin = pin;
}

void Beacon::start() {
  pinMode(LDRPin, INPUT);
  rAve[ROLL_AVE_SIZE] = {0};
  maxVal[2] = {0};
}

int Beacon::measure(int angle, int left, int right, Servo servo) {
  rAve[angle % ROLL_AVE_SIZE] = (short) analogRead(LDRPin);
  short newAve = 0;
  for(uint8_t i = 0; i < ROLL_AVE_SIZE; i++) {
    newAve += rAve[i];
  }
  newAve /= ROLL_AVE_SIZE;
  Serial.println(newAve);
  if(newAve > maxVal[0]) {
    maxVal[0] = newAve;
    maxVal[1] = angle;
  }

  if(angle == left || angle == right) {
    uint8_t maxAng = maxVal[1];

    start();
    return maxAng;
  }
  return -1;
}
