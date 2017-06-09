#include "IR.h"
#include "Arduino.h"

IR::IR(int robot) {
	if(robot == 1) {
		sensorPin = A0;
		selectPin = D2;
		selectPin = D3;
		selectPin = D4;
		sensorPinline1 = A1;
		sensorPinline2 = A4;
	} else {
		sensorPin = A0;
		selectPin = D2;
		selectPin = D3;
		selectPin = D4;
		sensorPinline1 = A1;
		sensorPinline2 = A4;
	}
}

void IR::setup() {
  pinMode(sensorPin, INPUT);
  pinMode(selectPin1, OUTPUT);
  pinMode(selectPin2, OUTPUT);
  pinMode(selectPin3, OUTPUT);

  pinMode(sensorPinline1, INPUT);
  pinMode(sensorPinline2, INPUT);
}

void IR::readLineSensor(){
Stateleft = analogRead(sensorPinline1);
Stateright = analogRead(sensorPinline2);
    
if (Stateleft<threshold && Stateright>threshold){
    thing = 1;
  }
  //right sensor sees tape
  if (Stateright<threshold && Stateleft>threshold){
    thing = 2;
  }
  //bot see tape
  if(Stateright<threshold && Stateleft<threshold){
    thing = 3;
  }
  //no sensor sees tape
  if (Stateleft>threshold && Stateright>threshold){
    thing = 0;
  }
}  
void IR::readRockSensor(){


  //select channel
      switch(i){
        case 0:
          digitalWrite(selectPin1,LOW);
          digitalWrite(selectPin2,LOW);
          digitalWrite(selectPin3,LOW);
          channel=1;
          break;
        case 1:
          digitalWrite(selectPin1,LOW);
          digitalWrite(selectPin2,LOW);
          digitalWrite(selectPin3,HIGH);
          channel=2;
          break;
        case 2:
          digitalWrite(selectPin1,LOW);
          digitalWrite(selectPin2,HIGH);
          digitalWrite(selectPin3,LOW);
          channel=3;
          break;
        case 3:
          digitalWrite(selectPin1,LOW);
          digitalWrite(selectPin2,HIGH);
          digitalWrite(selectPin3,HIGH);
          channel=4;
          break;
        case 4:
          digitalWrite(selectPin1,HIGH);
          digitalWrite(selectPin2,LOW);
          digitalWrite(selectPin3,LOW);
          channel=5;
          break;
        case 5:
          digitalWrite(selectPin1,HIGH);
          digitalWrite(selectPin2,LOW);
          digitalWrite(selectPin3,HIGH);
          channel=6;
          break;
        case 6:
          digitalWrite(selectPin1,HIGH);
          digitalWrite(selectPin2,HIGH);
          digitalWrite(selectPin3,LOW);
          channel=7;
          break;
        case 7:
          digitalWrite(selectPin1,HIGH);
          digitalWrite(selectPin2,HIGH);
          digitalWrite(selectPin3,HIGH);
          channel=8;
          break;
        
    }
	delay(10);
	//read analog value and update store max
		rockSensorValue=analogRead(sensorPin);
		if (rockSensorValue>rockSensorValueMax){
			rocksSensorValueMax=rockSensorValue;
			rockChannel=channel;
		}	
	}
	//check if valid (not a line)
	if(rockSensorValueMax>=minimumValue){
		rockSensorValueValidated=rockSensorValue; //update sensor value
	}else{
		channel=0;
	}
}

void IR::angleRockRobot{
	if(channel!=0){
		if(channel!=4 && channel!=5){
			switch(channel){
				case 1:
					angleRockRobot=(-1)*((40/9)*4-(20/9));
				case 2:
					angleRockRobot=(-1)*((40/9)*3-(20/9));
				case 3:
					angleRockRobot=(-1)*((40/9)*2-(20/9));
				case 6:
					angleRockRobot=(1)*((40/9)*2-(20/9));
				case 7:
					angleRockRobot=(1)*((40/9)*3-(20/9));
				case 8:
					angleRockRobot=(1)*((40/9)*4-(20/9));
			}
		}else{
			//balance between two middle sensors, for this you need min and max value of the sensors
			selectPin1=LOW;
			selectPin2=HIGH;
			selectPin3=HIGH;
			rockSensor4Value=analogRead(sensorPin);
			selectPin1=HIGH;
			selectPin2=LOW;
			selectPin3=LOW;
			rockSensor5Value=analogRead(sensorPin)
			angleRockRobot=((rockSensor4Value-rockSensor5Value)/(maxRockSensorValue-minRockSensorValue))
		}
	}else{
		angleRockRobot=0;
	}
}
