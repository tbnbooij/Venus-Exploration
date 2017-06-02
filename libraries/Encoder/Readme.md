# Encoder library
This library handles the two rotary encoders on the wheels (noticing the 8 holes in the wheels)
## Constructor
Create a new "Encoder" instance with the following code:
```c++
Encoder variableName = new Encoder(1|2) // argument is the robot number
```
## Methods
### void setup()
Call this function in the `setup()` of the main algorithm
### void updateRelativePosition(int leftWheelStatus, int rightWheelStatus)
Call this function in the `loop()` to read the encoders and update the `x`, `y` and `angle` variables.
### boolean checkDistanceDriven(float xStart, float yStart, float distance)
Whenever the robot has to drive a fixed distance, call `Motion::startDriving()` and save the `x`and `y` coordinates with the `getX()` and `getY()` methods in the main algortithm. Pass those to this method and it will return `true` when the difference between current coordinates and the passed arguments gives a greater/equal distance than the input distance
### boolean checkAngleTurned(float begin, float a, boolean increasing)
Similar to the `checkDistanceDriven` method; returns true after the difference between the current angle and the saved angle - when the turning started - passed the `a` argument. The argument `increasing` will tell the method whether the robot turns left (`true`) or to the right (`false`).
### float getX()
Method which returns the current `x` coordinate. The variable itself cannot be edited directly, as it is private.
### float getY()
Method which returns the current `y` coordinate. The variable itself cannot be edited directly, as it is declared private.
### float getAngle();
Method which returns the current `angle` coordinate. The variable itself cannot be edited directly, as it is declared private. This angle will be mapped back between 0 and 2&pi; radians. (e.g. 3&pi; becomes &pi;)
### float getRawAngle();
Method which returns the current `angle` coordinate. The variable itself cannot be edited directly, as it is declared private. The angle will *not* be mapped back. (e.g. 3&pi; will be returned as 3&pi;)
### String test();
Function which returns a String `"1"` to test the library as a whole.