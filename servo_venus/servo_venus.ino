// Robotics with the BOE Shield - ForwardTenSeconds
// Make the BOE Shield-Bot roll forward for ten seconds, then stop.

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
Servo servoGrab;


 
void setup()                                 // Built-in initialization block
{

}  
 
void loop()                                  // Main loop auto-repeats
{     
  servoLeft.attach(13);                      // Attach left signal to pin 13
  servoRight.attach(12);                     // Attach right signal to pin 12
  servoGrab.attach(11);
  

  // Full speed forward
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);        // Right wheel clockwise
  delay(1000);

  
  
  servoGrab.writeMicroseconds(300);
  delay(1000);
  servoGrab.writeMicroseconds(3000);
  delay(1000);

  
  
    servoLeft.detach();                        // Stop sending servo signals
  servoRight.detach();                    // Empty, nothing needs repeating
  servoGrab.detach();
}
