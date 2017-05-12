// Robotics with the BOE Shield - ForwardTenSeconds
// Make the BOE Shield-Bot roll forward for ten seconds, then stop.

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
 
void setup()                                 // Built-in initialization block
{
  
}  
 
void loop()                                  // Main loop auto-repeats
{     
  servoLeft.attach(13);                      // Attach left signal to pin 13
  servoRight.attach(12);                     // Attach right signal to pin 12
 
  

  // Full speed forward
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
 
  
  //servoLeft.detach();                        // Stop sending servo signals
  //servoRight.detach();                    // Empty, nothing needs repeating
}

void startDriving(float dist) {
//  isDriving = true;
  //distance = dist;
  
}

