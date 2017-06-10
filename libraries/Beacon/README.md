# Beacon Library

Here's how you implement the beacon library in the ultrasound function.

1. Initialize a beacon object with the LDR pin (as an uint8_t).
2. Add the start method at the beginning of the ultrasound loop.
3. Add the measure method in every loop of the servo movement.
4. Add the stop method at the end of the function. This function returns 0 for perpendicular, 1/-1 for left or right (haven't calibrated it yet).
