/*
  Wireless.h - Library for sending and receiving messages wirelessly
  Created by T.B.N. Booij, May 26, 2017.
  Written for the Venus Exploration project
	Eindhoven University of Technology
*/

#ifndef Wireless_h
#define Wireless_h
#define QUEUE_SIZE 10
#define PACKET_SIZE 10
#define IMM_READ_DELAY 50
#define DEBUG true

#include "Arduino.h"

class Wireless
{
	public:
		Wireless(int seed);

		int immRead();
		void createMessages(int amFilled);
		int getNoFilled(String queue[]);
		void addToQueue(String input, String queue[]);
		void splitMessages(String msgs);
		void searchPacket(String buffer);
		void sendId(String id);

    void send();
		void read();
		void sendLater(String msg);
		void printQueue(String queue[]);
		void go();
		void debugMessage(String function, String msg);
		void clearQueue(String queue[])
};

#endif
