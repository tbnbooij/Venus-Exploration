# Beacon (Library)

The beacon library is a lot simpler than the intial wireless library (and rightly so). However, it does contain a couple of safety nets to prevent false readings from overtaking the return values.

Here is how it works.

## Step one: Sweep and Measure
The servo sweeps across a given angle and measures the readings from the LDR sensor circuit. These readings are stored in an integer array.

## Step two: Moving average
Calculate the moving average of every entry in the array to prevent measurement errors from overtaking the return value.

## Step three: Find the maximum
Now just find the maximum in the array.

## Step four: Return left/right
Based on the index of the maximal value, we can return a -1 (right), 0 (in front of robot) or a 1 (left) to help the robot find the lab.

## Functions
### Beacon::Beacon()
Input variables: ```int _normal, int _angle, int _USServo, int _intDelay```
Constructor of the class. Takes in the actual normal of the servo, the angle across the servo will sweep, the pin number of the servo and an internal delay value for sweeping the servo (might be needed while testing).

### Beacon::sweep()
Sweep the servo, read the values, apply rolling average and return a direction. This is the **only** real function in the library. Hurrah!
Return values:
* -1 corresponds to "to the right of the robot"
* 0 corresponds to "in front of robot"
* 1 correspons to "to the left of the robot"
