# Encoder library
This library handles the two rotary encoders on the wheels (noticing the 8 holes in the wheels)
## Constructor
Create a new "Encoder" instance with the following code:
```c++
Encoder variableName(1|2) // argument is the robot number
```
Now the class can be used the following way, with the [test function](#string-test):
```c++
String t = variableName.test(); // t == "1" 
```
## Methods
### void setup()
Call this function in the `setup()` of the main algorithm
### void updateRelativePosition(int leftWheelStatus, int rightWheelStatus)
Call this function in the `loop()` to read the encoders and update the `x`, `y` and `angle` variables.
### boolean checkDistanceDriven(float distance)
Whenever the robot has to drive a fixed distance, call `Motion::startDriving()`. Call this function in the `loop()`. It will return `true` when the distance is covered (since first calling the function with that distance).
### boolean checkAngleTurned(float a)
Similar to the `checkDistanceDriven` function; returns true after the difference between the current angle and the saved angle - when the turning started - passed the `a` argument. The angle is positive when turning left and negative when turning right.
### float getTurnAngle()
This method returns the angle must turn to face the base, either negative to turn right or positive to turn left.
### float getX()
Method which returns the current `x` coordinate. The variable itself cannot be edited directly, as it is private.
### float getY()
Method which returns the current `y` coordinate. The variable itself cannot be edited directly, as it is declared private.
### float getAngle()
Method which returns the current `angle` coordinate. The variable itself cannot be edited directly, as it is declared private. This angle will be mapped back between -&pi; and &pi; radians. (e.g. 3&pi; becomes &pi;)
### float getRawAngle()
Method which returns the current `angle` coordinate. The variable itself cannot be edited directly, as it is declared private. The angle will *not* be mapped back. (e.g. 3&pi; will be returned as 3&pi;)
### float boundAngle(float angle)
This function will add/subtract 2&pi; until it gets between -&pi; and &pi;
### String test()
Function which returns a String `"1"` to test the library as a whole.