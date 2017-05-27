/*
  Wireless.cpp - Library for sending and receiving messages wirelessly
  Created by T.B.N. Booij, May 26, 2017.
  Written for the Venus Exploration project
	Eindhoven University of Technology
*/

#include "Wireless.h"
#include "Arduino.h"

String readQueue[QUEUE_SIZE] = {""};
String sendQueue[QUEUE_SIZE] = {""};
String msgQueue[QUEUE_SIZE] = {""};
String readBuffer = "";
int amReads = -1;
int pingId = -1;
bool pingPriority = false;

// Constructor
Wireless::Wireless(int seed) {
	Serial.begin(9600);
	Serial.setTimeout(50);
	randomSeed(seed);
}

// Print a debugging message
void Wireless::debugMessage(String function, String msg) {
	if(DEBUG) {
		Serial.println(("[*] " + function) + (": " + msg));
	}
}

// Send gateway
void Wireless::send() {
	String funcName = "SEND";
  // Get the amount of filled spaces in the queue
  int8_t filled = getNoFilled(sendQueue);

  // If there is something to send ...
  if(filled > 0) {
    // Create the messages
    createMessages(filled);

    printQueue(msgQueue);

    int8_t amFilled = getNoFilled(msgQueue);

		bool block = true;
		debugMessage(funcName, "Waiting for [*]");
		while(block) {
			String buffer = Serial.readString();
			int8_t ob = buffer.indexOf('[');
			int8_t cb = buffer.indexOf(']', ob);
			int8_t star = buffer.indexOf('*', ob);

			if((ob != -1 && cb != -1 && star != -1) && (ob+1 == star && cb-1 == star)) {
				block = false;
			}
		}

    int oid = random(0,10000);
    int recOid = -1;

		debugMessage(funcName, "init");
    while(oid != recOid) {
      Serial.print(("[#" + String(amFilled)) + ("@" + (String(oid) + "]")));
      recOid = immRead();
      delay(IMM_READ_DELAY);
    }

    for(int i = 0; i < amFilled; i++) {
      String currentMsg = msgQueue[i];
			debugMessage(funcName, "Send - " + currentMsg);
      int id = currentMsg.substring(currentMsg.indexOf('@')+1,currentMsg.indexOf(']')).toInt();
      Serial.print(id);
      int recId = -1;

			debugMessage(funcName, "Wait");
      while(recId != id) {
        Serial.print(currentMsg);
        recId = immRead();
        delay(IMM_READ_DELAY);
      }
    }
  }
	pingId = -1;
	clearQueue(sendQueue);
	clearQueue(msgQueue);
}

// Immediate read - After sending message on sender side
int Wireless::immRead() {
	String funcName = "IMMREAD";
  if(Serial.available() > 0) {
    String buffer = Serial.readString();
    int8_t ob = buffer.indexOf('[');
    int8_t cb = buffer.indexOf(']',ob);
    int8_t dollar = buffer.indexOf('$',ob);

    if(ob != -1 && cb != -1 && dollar != -1) {
      if(dollar < cb && dollar > ob) {
				int recId = buffer.substring(dollar+1,cb).toInt();
				debugMessage(funcName, String(recId));
        return recId;
      }
      else {
				debugMessage(funcName, "f1");
        return -1;
      }
    }
    else {
			debugMessage(funcName, "f2");
      return -1;
    }
  }
  else {
		debugMessage(funcName, "f3");
    return -1;
  }
}

// Print a queue (DEBUG)
void Wireless::printQueue(String queue[]) {
	if(DEBUG) {
		for(int i = 0; i < QUEUE_SIZE; i++) {
			Serial.print(String(i+1) + ": ");
			if(queue[i] == "") {
				Serial.println("-");
			}
			else {
				Serial.println(queue[i]);
			}
		}
	}
}

// Create messages from the sendQueue
void Wireless::createMessages(int amFilled) {
  String tmp = "";
  for(int i = 0; i < amFilled; i++) {
    String potTmp = tmp;
    if(tmp != "") {
      potTmp += '|';
    }

    potTmp += sendQueue[i];

    if(potTmp.length() <= PACKET_SIZE && (i+1) != amFilled) {
      tmp = potTmp;
    }
    else {
      String msg = '[' + potTmp;
      msg += ('@' + String(random(0,10000)));
      msg += ']';
			debugMessage("CREATE", msg);
      addToQueue(msg, msgQueue);
      tmp = "";
    }
  }
}

// Get the amount of filled spots in a queue
int Wireless::getNoFilled(String queue[]) {
  int8_t filled = 0;
  for(int i = 0; i < QUEUE_SIZE; i++) {
    if(queue[i] != "") {
      filled++;
    }
  }
	debugMessage("NOFILL", String(filled));
  return filled;
}

// Add an item to a queue
void Wireless::addToQueue(String input, String queue[]) {
  // Iterator and blocking boolean
  uint8_t i = 0;
  bool block = true;

  // Just test every single spot in the array UNTIL we hit an empty spot
  // If we don't hit an empty spot, then we should hard-code a larger array
  if(input != "") {
    while(block && i < QUEUE_SIZE) {
      // If spot i is empty
      if(queue[i] == "") {
        queue[i] = input;
        block = false;
				debugMessage("ADDQUE", input);
      }
      else {
        // Just move up one space in the array and run this test again
        i++;
      }
    }
  }
}

// Split a packet string to seperate messages
void Wireless::splitMessages(String msgs) {
	String funcName = "SPLIT";
  // Find the first split icon
  int8_t split = msgs.indexOf('|');

  // Are there multiple messages in the packet?
  if(split != -1) {
    // Then just find the first message, store it in the read queue
    // and re-call this function starting at the second message
		String newMessage = msgs.substring(0,split);
		debugMessage(funcName, newMessage);
    addToQueue(newMessage, readQueue);
    splitMessages(msgs.substring(split+1));
  }
  else {
    // There is only one message (left)
    // Store this message in the read queue
		debugMessage(funcName, msgs);
    addToQueue(msgs, readQueue);
  }
}

// Try to find a packet in a serial buffer
void Wireless::searchPacket(String buffer) {
	String funcName = "SEARCH";
	// Opening bracket
  int8_t ob = buffer.indexOf('[');

  // Closing bracket
  int8_t cb = buffer.indexOf(']', ob);

  // @ symbol (before the ID)
  int8_t at = buffer.indexOf('@', ob);

  // # symbol (indicates inital ID)
  int8_t hs = buffer.indexOf('#');

  // These character ALL have to be in the buffer
  if(ob != -1 && cb != -1 && at != -1) {
    // The id indicator has to lie between the opening and the closing bracket
    // Because DUH
    if(at > ob && at < cb) {
      // Does the buffer contain an opening ID? (hashtag)
      String totalPacket = buffer.substring(ob,cb);
			debugMessage(funcName, totalPacket);

      // If the buffer has a hashtag -> Opening tag
      if(hs != -1) {
        String packet = buffer.substring(ob+1,cb);
        // Set the amount of expected messages
        amReads = buffer.substring(hs+1,at).toInt();
				debugMessage(funcName, String(amReads));

        // Send an ID for acknowledgement
        sendId(buffer.substring(at+1,cb));
      }
      else {
        String packet = buffer.substring(ob+1,at);
				debugMessage(funcName, packet);

        // Send an ID for acknowledgement of the message
        sendId(buffer.substring(at+1,cb));

        // If the packet contains NEW data
        if(readBuffer != totalPacket) {
					debugMessage(funcName, "new");
          // Split and store the message(s)
          splitMessages(packet);


					// Keep track of the amount of expected transmissions
					if(amReads == 1) {
						amReads = -1;

						// This is the last transmission => No checks anymore
						// So as a safety precaution send the ID another 3 times
						for(int i = 0; i < 3; i++) {
							sendId(buffer.substring(at+1,cb));
							delay(30);
						}
					}
					else {
						amReads--;
					}

          // And update the readBuffer in order to prevent duplicates
          readBuffer = totalPacket;
        }
      }
    }
  }
}

// Send the ID of a message (return to sender)
void Wireless::sendId(String id) {
  Serial.println(("[$" + id) + "]");
}

// Public function to add a message to the sendQueue
void Wireless::sendLater(String msg) {
	String funcName = "SEND_L";
	debugMessage(funcName, msg);
	addToQueue(msg, sendQueue);

	if(pingId == -1) {
		pingId = random(10,10000);
		String pingMsg = ('>' + String(pingId)) + '~';
		Serial.print(pingMsg);
		debugMessage(funcName, pingMsg);
	}
}

// Read gateway
void Wireless::read() {
	for(int i = 0; i < 3; i++) {
		Serial.print("[*]");
	}

	// Initialize the amReads variable to open the door to the while loop
  amReads = -2;
	// At initialization or when messages are still expected
  while(amReads == -2 || amReads > 0) {
		// If the serial buffer isn't empty
    if(Serial.available() > 0) {
			debugMessage("READ", "!!!");
			// Search the buffer for a packet of data
      searchPacket(Serial.readString());
    }
    delay(50);
  }
  printQueue(readQueue);
}

// Wipes all spaces of a queue
void Wireless::clearQueue(String queue[]) {
	for(int i = 0; i < QUEUE_SIZE; i++) {
		if(queue[i] != "") {
			queue[i] = "";
		}
		else {
			break;
		}
	}
}

// GLOBAL GATEWAY FUNCTION
void Wireless::go() {
	String funcName = "GO";
	// Get everything out of the buffer!
	String buffer = Serial.readString();
	int initPing = buffer.indexOf('>');

	if(initPing != -1) {
		int endHash = buffer.indexOf('~',initPing);

		// Does the buffer contain a ping message?
		if(endHash != -1) {
			String oid = buffer.substring(initPing+1, endHash);
			int oidInt = oid.toInt();

			if(oidInt > pingId) {
				debugMessage(funcName, "read1");
				read();
			}
			else if(oidInt == pingId) {
				if(pingPriority) {
					debugMessage(funcName, "send4");
					send();
				}
				else {
					debugMessage(funcName, "read2");
				}
			}
			else {
				debugMessage(funcName, "send1");
				send();
			}
		}
		else {
			// We've received NO ping message
			// Do we want to send something?
			if(pingId > 0) {
				debugMessage(funcName, "send2");
				send();
			}
		}
	}
	else {
		if(pingId > 0) {
			// We've receive NO ping message
			// AND we want to send something
			debugMessage(funcName, "send3");
			send();
		}
	}
}
