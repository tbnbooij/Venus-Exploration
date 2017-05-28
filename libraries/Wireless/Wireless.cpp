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
String readBuffer = "";
int8_t amReads = -1;
int8_t pingId = -1;
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
    createPackets(filled);


    printQueue(sendQueue);

    int8_t amFilled = getNoFilled(sendQueue);

		debugMessage(funcName, "Waiting for [*]");

		int8_t retVal = -1;

		while(retVal != -2) {
			String buffer = Serial.readString();
			retVal = immRead();
		}

    int8_t oid = random(0,128);
    int8_t recOid = -1;

		debugMessage(funcName, "init");
    while(oid != recOid) {
      Serial.print(("[#" + String(amFilled)) + ("@" + (String(oid) + "]")));
      recOid = immRead();
    }

    for(int8_t i = 0; i < amFilled; i++) {
      String currentMsg = sendQueue[i];
			debugMessage(funcName, "Send - " + currentMsg);
      int8_t id = currentMsg.substring(currentMsg.indexOf('@')+1,currentMsg.indexOf(']')).toInt();
      Serial.print(id);
      int8_t recId = -1;

			debugMessage(funcName, "Wait");
      while(recId != id) {
        Serial.print(currentMsg);
        recId = immRead();

      }
    }
  }
	pingId = -1;
	clearQueue(sendQueue);
}

// Immediate read - After sending message on sender side
int8_t Wireless::immRead() {
	delay(IMM_READ_DELAY);
	String funcName = "IMMREAD";
  if(Serial.available() > 0) {
    String buffer = Serial.readString();
    int8_t ob = buffer.indexOf('[');
    int8_t cb = buffer.indexOf(']',ob);
    int8_t dollar = buffer.indexOf('$',ob);
		int8_t star = buffer.indexOf('*',ob);
		int8_t hyphen = buffer.indexOf('-',ob);

    if(ob != -1 && cb != -1) {
			if(dollar != -1 && (dollar < cb && dollar > ob)) {
					// Detected an ID tag!
					int8_t recId = buffer.substring(dollar+1,cb).toInt();
					debugMessage(funcName, String(recId));
					return recId;
			}

			if(star != -1 && (ob+1 == star && cb-1 == star)) {
				// Detected a START tag
				return -2;
			}

			if(hyphen != -1 && (ob+1 == hyphen && cb-1 == hyphen)) {
				return -3;
			}
		}
	}
	debugMessage(funcName,"fail");
	return -1;
}


// Print a queue (DEBUG)
void Wireless::printQueue(String queue[]) {
	if(DEBUG) {
		for(int8_t i = 0; i < QUEUE_SIZE; i++) {
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
void Wireless::createPackets(int8_t amFilled) {
  for(int8_t i = 0; i < amFilled; i++) {
		sendQueue[i] = ("[" + sendQueue[i]) + (("@" + String(random(0,128))) + "]");
  }
}

// Get the amount of filled spots in a queue
int8_t Wireless::getNoFilled(String queue[]) {
  int8_t filled = 0;
  for(int8_t i = 0; i < QUEUE_SIZE; i++) {
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
					addToQueue(packet, readQueue);


					// Keep track of the amount of expected transmissions
					if(amReads == 1) {
						amReads = -1;

						// This is the last transmission => No checks anymore
						// So as a safety precaution send the ID another 3 times
						for(int8_t i = 0; i < 3; i++) {
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
}

// Read gateway
void Wireless::read() {
	for(int8_t i = 0; i < 3; i++) {
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
	for(int8_t i = 0; i < QUEUE_SIZE; i++) {
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
	debugMessage(funcName,"Waiting for [-]");

	int8_t wait = -1;

	//  Wait for synchronization
	while(wait != -3) {
		wait = immRead();
		Serial.print("[-]");
	}
	// Empty out serial buffer
	Serial.readString();

	// Do we want to send something?
	if(getNoFilled(sendQueue) > 0) {
		pingId = random(1,128);
	}
	else {
		pingId = 0;
	}

	// Send a ping message
	String pingMsg = ('>' + String(pingId)) + '~';
	Serial.print(pingMsg);
	debugMessage(funcName, pingMsg);
	debugMessage(funcName, "PLEASE ENTER");
	if(DEBUG){delay(5000);};
	delay(100);

	// And read a received message
	String buffer = Serial.readString();
	int8_t initPing = buffer.indexOf('>');
	int8_t endTilde = buffer.indexOf('~', initPing);

	// Did we receive a ping message?
	if((initPing != -1 && endTilde != -1) && (initPing < endTilde)) {

		// Get the OTHER ping ID
		int8_t oid = buffer.substring(initPing+1, endTilde).toInt();

		if(oid == 0 && pingId >= 0) {
			debugMessage(funcName, "s");
			send();
		}
		else if(oid >= 0 && pingId == 0) {
			debugMessage(funcName, "r");
			read();
		}
		else if(oid >= 0 && pingId >= 0) {
			if(oid > pingId) {
				debugMessage(funcName, "r/s");
				read();
				send();
			}
			else if(oid == pingId) {
				if(pingPriority) {
					debugMessage(funcName, "s/r");
					send();
					read();
				}
				else {
					debugMessage(funcName, "r/s");
					read();
					send();
				}
			}
			else {
				debugMessage(funcName, "s/r");
				send();
				read();
			}
		}


		if(oid > pingId) {
			debugMessage(funcName, "r/s");
			read();
			send();
		}
		else if(oid == pingId) {
			if(pingPriority) {
				debugMessage(funcName, "s/r");
				send();
				read();
			}
			else {
				debugMessage(funcName, "r/s");
				read();
				send();
			}
		}
		else {
			debugMessage(funcName, "s/r");
			send();
			read();
		}
	}
}

// GRAVEYARD
/*

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


*/
