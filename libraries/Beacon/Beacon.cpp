#include "Beacon.h"
#include "Arduino.h"
#include "Servo.h"

Beacon::Beacon(int _normal, int _angle, int _USServo, int _intDelay) {
  normal = _normal;
  angle = _angle;
  USServo = _USServo;
  intDelay = _intDelay;
}

int Beacon::sweep() {
  s.attach(USServo);
  const int sample_size = 2*angle + 1;
  int readings[sample_size] = {0};
  int output[sample_size] = {0};
  int r_ave_len = round(((float) sample_size)/20)
  int z = 0;

  // Phase 1: Measure and store
  for(int i = normal - angle; i <= normal + angle; i++) {
    s.write(i);
    readings[z] = analogRead(LDRPin);
    delay(intDelay);
    z++;
  }
  s.detach(USServo);

  // Phase 2: Calculate moving average
  for(int i = 0; i < sample_size; i++) {
    int ave = 0;
    if(i < r_ave_len) {
      for(int k = 0; k < (i+1)) {
        ave += readings[k];
      }
    }
    else {
      for(int j = 0; j < r_ave_len; j++) {
        ave += readings[i - j];
      }
    }
    ave /= r_ave_len;
    output[i] = ave;
  }

  // Phase 3: Find maximum
  int maxVal[2] = {0,0}
  for(int i = 0; i < sample_size; i++) {
    if(output[i] > maxVal[0]) {
      maxVal[0] = output[i];
      maxVal[1] = i;
    }
  }

  // Phase 4: Return
  if((i+1) <= floor(sample_size/2)) {
    return -1;
  }
  else if((i+1) == ceil(sample_size/2)) {
    return 0;
  }
  else {
    return 1;
  }
}
