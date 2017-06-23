/*
  Wireless.h - Library for sending and receiving messages wirelessly
  Created by T.B.N. Booij, May 26, 2017.
  Written for the Venus Exploration project
	Eindhoven University of Technology
*/

#ifndef Wireless_h
#define Wireless_h
#define QUEUE_SIZE 10

#include "Arduino.h"

class Wireless
{
	private:
		int _read;
	public:

		Wireless();
		void send(String msg);
		void store(String msg);
		void printQueue(String queue[]);
		void process();
		void interpret();
		String sendQueue[QUEUE_SIZE] = {""};
		String readQueue[QUEUE_SIZE] = {""};

};

#endif
