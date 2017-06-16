#include "Beacon.h"
#include "Arduino.h"
#include "Servo.h"

Beacon::Beacon(uint8_t pin) {
  LDRPin = pin;
  pinMode(LDRPin, INPUT);
}

void Beacon::start() {
  rAve[ROLL_AVE_SIZE] = {0};
  maxVal[2] = {0};
}

void Beacon::measure(int angle, int left, int right, Servo servo, bool demo) {
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
    float ratio = ((float) (maxVal[1] - right))/((float) (left-right));
    /*
    if(ratio == 0.5) {
      Serial.println("RIGHT IN FRONT OF IT!");
    }
    else if (ratio < 0.5) {
      Serial.println("TO THE RIGHT!");
    }
    else {
      Serial.println("TO THE LEFT!");
    }*/
    if(demo) {
      servo.write(maxVal[1]);
      delay(2000);
      if(angle == left) {
        servo.write(left);
      }
      else {
        servo.write(right);
      }
      delay(1000);
    }
    start();
  }
}
