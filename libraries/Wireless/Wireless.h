#ifndef Wireless_h
#define Wireless_h

#include "Arduino.h"

class Wireless
{
	private:

	public:
    Wireless();
    void send(char msg);
    char read();
};

#endif
