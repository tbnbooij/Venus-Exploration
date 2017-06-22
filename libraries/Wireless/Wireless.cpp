#include "Wireless.h"
#include "Arduino.h"

Wireless::Wireless() {

}

void Wireless::send(char msg) {
  Serial.print(msg);
}

char Wireless::read() {
  if(Serial.available() > 0) {
    String buffer = Serial.readString();
    uint8_t i = 0;
    while(i < buffer.length()) {
      if(buffer[i] >= 65 && buffer[i] <= 90) {
        return buffer[i];
      }
      else {
        i++;
      }
    }
    return -2;
  }
  return -1;
}
