// For the constant M.PI
#include <math.h>;

const float radius = 1.0;
float circumference = 0;

const int leftEncoder = 7;
const int rightEncoder = 8;

int leftEncoderState = 0;
int lastLeftEncoderState = 0;
int rightEncoderState = 0;
int lastRightEncoderState = 0;

int x = 0;
int y = 0;
int angle = 0;

void setup() {
  circumference = 2 * M.PI * radius;
  Serial.begin(9600);
  pinMode(leftEncoder, INPUT);
  pinMode(rightEncoder, INPUT);
}

void loop() {
  readEncoder();
}

void readEncoder() {
  float leftDelta = 0.0;
  float rightDelta = 0.0;
  
  leftEncoderState = digitalRead(leftEncoder);
  if(leftEncoderState != lastLeftEncoderState) {
    if(leftEncoderState == HIGH) {
      //rising trigger
      leftDelta = circumference / 8;
    }
  }
  lastLeftEncoderState = leftEncoderState;

  rightEncoderState = digitalRead(rightEncoder);
  if(rightEncoderState != lastRightEncoderState) {
    if(rightEncoderState == HIGH) {
      //rising trigger
      rightDelta = circumference / 8;
    }
  }
  lastRightEncoderState = rightEncoderState;

  
  // leftDelta and rightDelta = distance that the left and right wheel have moved along
  //  the ground
  // https://robotics.stackexchange.com/questions/1653/calculate-position-of-differential-drive-robot
  if (fabs(leftDelta - rightDelta) < 1.0e-6) { // basically going straight
      new_x = x + leftDelta * cos(heading);
      new_y = y + rightDelta * sin(heading);
      new_heading = heading;
  } else {
      float R = unitsAxisWidth * (leftDelta + rightDelta) / (2 * (rightDelta - leftDelta)),
            wd = (rightDelta - leftDelta) / unitsAxisWidth;
  
      new_x = x + R * sin(wd + heading) - R * sin(heading);
      new_y = y - R * cos(wd + heading) + R * cos(heading);
      new_heading = boundAngle(heading + wd);
  }
}

