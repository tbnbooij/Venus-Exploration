# Wireless Communication

This is the library for the wireless communication. I know, this file seems long, but **don't be scared**; I'll explain how this works.

## Table of contents
- [How to use](#how-to-use)
- [An informal explanation of the principle of operation](#an-informal-explanation-of-the-principle-of-operation)
  * [Step 1 - Once upon a time](#step-1---once-upon-a-time)
  * [Step 2 - Go!](#step-2---go)
  * [Step 3 - And they lived happily every after](#step-3---and-they-lived-happily-every-after)
- [Definitions](#definitions)
  * [QUEUE_SIZE](#queue_size)
  * [PACKET_SIZE](#packet_size)
  * [IMM_READ_DELAY](#imm_read_delay)
  * [DEBUG](#debug)
- [Global variables](#global-variables)
  * [readQueue](#readqueue)
  * [sendQueue](#sendqueue)
  * [msgQueue](#msgqueue)
  * [readBuffer](#readbuffer)
  * [amReads](#amreads)
  * [pingId](#pingid)
  * [pingPriority](#pingpriority)
- [Functions](#functions)
  * [Wireless()](#wireless)
  * [Wireless::go()](#wirelessgo)
  * [Wireless::read()](#wirelessread)
  * [Wireless::send()](#wirelesssend)
  * [Wireless::debugMessage()](#wirelessdebugmessage)
  * [Wireless::printQueue()](#wirelessprintqueue)
  * [Wireless::sendLater()](#wirelesssendlater)
  * [Wireless::searchPacket()](#wirelesssearchpacket)
  * [Wireless::sendId()](#wirelesssendid)
  * [Wireless::splitMessages()](#wirelesssplitmessages)
  * [Wireless::addToQueue()](#wirelessaddtoqueue)
  * [Wireless::getNoFilled()](#wirelessgetnofilled)
  * [Wireless::createMessages()](#wirelesscreatemessages)
  * [Wireless::immRead()](#wirelessimmread)


## How to use
Firsly, import the library into the Arduino sketch. and create an instance of the class.

```Arduino
#include <Wireless.h>

void setup() {
  Wireless wireless(123);
}
```

If you want the robot to send something to the other robot, then add the message to the queue with ```.sendLater()```.

```Arduino
wireless.sendLater("HelloWorld!");
```

At regular moments during the main loop you can call the ```.go()``` method to send the messages to the other robot.

```Arduino
wireless.go();
```

## An informal explanation of the principle of operation

### Step 1 - Once upon a time
there were two robots, who lived in a land far, far away. But, ehem, let's get back to wireless communication. The two robots have to be able to send messages back and forth. For the sake of simplicity, I'll give them names. The sender will be called **Romeo** and the receiver will be called **Juliet**. Both robots have created an instance of the ```Wireless``` class.

So, Romeo wants to send a message to Juliet; let's say it is ```helloJuliet```. Firstly, he calls ```.sendLater("helloJulet")``` on his ```Wireless``` object. This adds the message to the ```sendQueue``` (a fancy word for: a list that contains the words Romeo wants to send in a second). Because this is the first item in the ```sendQueue```, Romeo creates a ```pingId``` (a number that indicates who gets to send a message and who will read for messages) and sends it to Juliet (syntax: ```>pingId~```). If Juliet has nothing to send, Romeo will have priority. If Juliet **and** Romeo want to send something, the robot with the highest ```pingId``` will be first to send.

So, all in all, when a robot wants to send something firstly some sort of turn order has to be established.

### Step 2 - Go!
At multiple moments in the loop, the ```.go()``` method is called. This function determines the aforementioned turn order and assigns both robots to their respective roles (read/send). These actions are tied to different functions with very vague and unexpected names: ```.read()``` and ```.send()```. The sender will create composite messages called **packets**. These have a very specific syntax: ```[messages@id]``` in which ```messages``` can be one or more messages and id is a random integer. If multiple messages are put into a packet, it will look like this: ```[hello|world|how|are|you@123]```.

So, Romeo will create these packets. But before he can send them, he wants to receive ```[*]``` from Juliet. That message indicates that Juliet has entered read mode and that Romeo can start sending messages. The first packet Romeo sends will be a bit different than the previously described ones; it looks like this: ```[#num@id]```. ```num``` is the amount of _packets_ that Romeo will send to Juliet. Now, just like before, Romeo will wait for something that Juliet sends. This time, it will be this message: ```[$id]``` (```id``` is the id from the packet). Interpret this as a sort of _aye-aye_ from Juliet; it indicates that she has received and processed a packet.

The actual packets will now be sent in a similar fashon: Romeo sends a packet, Juliet responds with the id. Only when Romeo receives the id will he switch to the next packet. Juliet will decipher the packets and place the messages in the ```readQueue```, which holds all the received messages for later processing.

### Step 3 - And they lived happily every after
This concludes the entire process. Romeo has sent the message to Juliet. However, I haven't written any functions yet for the interpretation of the messages, so...

**The End**


## Definitions

### QUEUE_SIZE
The amount of spaces in a queue.

### PACKET_SIZE
An approximate amount of characters in the body of a packet.

### IMM_READ_DELAY
The amount of time in milliseconds the Arduino waits between consecutive immediate reads (see ```Wireless::immRead()```).

### DEBUG
Boolean that indiates whether the code has to be used in debugging mode. When true, the function ```Wireless::debugMessage()``` and ```Wireless::printQueue()``` will print to the Serial monitor.

## Global variables

### readQueue
A queue (string array of size ```QUEUE_SIZE```) for all the messages that have been received.

### sendQueue
A queue (string array of size ```QUEUE_SIZE```) for all the messages that have to be sent.

### msgQueue
A queue (string array of size ```QUEUE_SIZE```) for all the messages that are created by ```Wireless::createMessages()```.

### readBuffer
A (usually empty) string used to determine whether a received packet has already been processed (in order to prevent duplicates).

### amReads
An integer that indicates how reads still have to be made (i.e. the amount of _expected_ packets by the receiver).

### pingId
An integer for determining sending priority.

### pingPriority
In case the pingIds of both robots are equal (it's unlikely, but it **could** happen), then this boolean will determine whether the robot has priorty or not. This boolean has to be manually set when uploading the script to the robots.

## Functions

### Wireless()
The constructor of the class. Takes in an integer for the as a seed for the ```random()``` function.

**Input**: ```int seed```
**Output**: ```void```

### Wireless::go()
The go-to (pun intended 😃) function for wireless communication. Automatically creates a connection and established unidirectional message flow.

**Input**: ```int seed```
**Output**: ```void```

_Note: If everything works as it should, this will be the only function that is needed for wireless communication._

### Wireless::read()
The function that automates the reading of incoming data.

**Input**: ```void```
**Output**: ```void```

### Wireless::send()
The function that automates the sending of outgoing data.

**Input**: ```void```
**Output**: ```void```

### Wireless::debugMessage()
Creates a console-like message (only if the DEBUG variable is true).

**Input**: ```String function, String message```
**Output**: ```void```
**Serial Output**: ```[*] FUNCTION: MESSAGE```

### Wireless::printQueue()
Gives a graphical representation of all spaces in a queue (in the Serial monitor).

**Input**: ```Sting queue[]```
**Output**: ```void```
**Serial Output**:
```
1. Hello
2. World
3. -
4. -
...
```

### Wireless::sendLater()
Adds a string to the ```sendQueue``` and creates a ping message if it is the first item in the ```sendQueue```.

**Input**: ```String message```
**Output**: ```void```
**Serial Output**: ```Optional: ping message | >123~```

### Wireless::searchPacket()
Takes in a serial buffer and tries to search for a packet of syntax ```[message@id]``` or ```[#numberExpectedMessages@id]```.

**Input**: ```String serialBuffer```
**Output**: ```void```

### Wireless::sendId()
Takes in an id (number) and prints an id return tag.

**Input**: ```int id```
**Output**: ```void```
**Serial Output**: ```[$id]```

### Wireless::splitMessages()
Takes in the body of a packet (a set of messages) and splits these into seperate messages. These will be passed to ```Wireless::addToQueue()``` to add them to the ```readQueue```.

**Input**: ```int messages```
**Output**: ```void```

### Wireless::addToQueue()
Takes in a string input and a String queue and adds the input to the first vacant spot in that queue.

**Input**: ```String input, String queue[]```
**Output**: ```void```

### Wireless::getNoFilled()
Takes in a queue and returns the amount of filled spaces.

**Input**: ```String queue[]```
**Output**: ```int amountOfFiledSpaces```

### Wireless::createMessages()
Creates larger conglomerate messages of single items in the ```sendQueue``` to reduce the amount of transactions. Takes in the amount of filled spaces in the ```sendQueue``` (```int```).

**Input**: ```int amFilled```
**Output**: ```void```

### Wireless::immRead()
(Read: Immediate read) Used in ```Wireless::send()```. Function that returns the id of an id tag that has been returned by the receiver **if** it finds a return tag in the serial buffer (else it returns -1).

**Input**: ```void```
**Output**: ```int id```
