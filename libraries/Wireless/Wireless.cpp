/*
  Wireless.cpp - Library for sending and receiving messages wirelessly
  Created by T.B.N. Booij, May 26, 2017.
  Written for the Venus Exploration project
	Eindhoven University of Technology
*/

#include "Wireless.h"
#include "Arduino.h"

Wireless::Wireless(int read, int send) {
  Serial.begin(9600);
  Serial.setTimeout(100);
  _read = read;
  _send = send;
  pinMode(_read, OUTPUT);
  pinMode(_send, OUTPUT);
}

void Wireless::send(String msg) {
  pinMode(_send,1);
  Serial.print("#" + (msg + "!"));
  delay(50);
  pinMode(_send,0);
}

void Wireless::store(String msg) {
  digitalWrite(_read, 1);
  for(int i = 0; i < QUEUE_SIZE; i++) {
    if(readQueue[i] == "") {
      readQueue[i] = msg;
    }
  }
  digitalWrite(_read, 0);
}

void Wireless::process() {
  for(int i = 0; i < QUEUE_SIZE; i++) {
    if(readQueue[i] != "") {
      String buffer = readQueue[i];
      readQueue[i] = "";

      int hash = buffer.indexOf('#');
      int excl = buffer.indexOf('!');

      if(hash > excl) {
        excl = buffer.indexOf('!', hash);
      }

      if((hash != -1 && excl != -1) && excl > hash) {
        while(buffer.substring(hash+1, excl).indexOf('#') != -1) {
          hash = buffer.indexOf('#', hash);
        }
        interpret(buffer.substring(hash+1, excl));
      }
    }
    else {
      break;
    }
  }
}

void Wireless::interpret(String msg) {
  int firstNum = -1;

  for(int i = msg.length() - 1; i >= 0; i--) {
    if(msg[i].toCharArray()[0] < 48 || msg[i].toCharArray()[0] > 57) {
        firstNum = i + 1;
    }
  }

  int recNum = -1;
  String core = "";
  if(firstNum != 1) {
    recNum = msg.substring(firstNum, msg.length() - 1).toInt();
    core = msg.substring(0, firstNum);
  }
  else {
    core = msg;
  }

  // NOW JUST USE A SWITCH!


}
