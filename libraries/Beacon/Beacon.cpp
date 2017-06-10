#include "Beacon.h"
#include "Arduino.h"

Beacon::Beacon(uint8_t pin) {
  LDRPin = pin;
  pinMode(LDRPin, INPUT);
}

void Beacon::start() {
  rAve[3] = {0};
  iterator = 0;
  maxVal[2] = {0};
}

void Beacon::measure() {
  rAve[iterator % 3] = (short) analogRead(LDRPin);
  short newAve = 0;
  for(uint8_t i = 0; i < 3; i++) {
    newAve += rAve[i];
  }
  newAve /= 3;
  if(newAve > maxVal[0]) {
    maxVal[0] = newAve;
    maxVal[1] = iterator;
  }
  iterator++;
}

int Beacon::stop() {
  uint8_t end = iterator - 1;
  float ratio = ((float) iterator)/((float) end);
  if(ratio == 0.5) {
    return 0;
  }
  else if (ratio > 0.5) {
    return 1;
  }
  else {
    return -1;
  }
}
