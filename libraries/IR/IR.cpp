#include "IR.h"
#include "Arduino.h"

IR::IR(int robot) {
	if(robot == 1) {
		sensorPin = A0;
		selectPin1 = 5;
		selectPin2 = 3;
		selectPin3 = 4;
		sensorPinline1 = A1;
		sensorPinline2 = A4;
	}	else {
		sensorPin = A0;
		selectPin1 = 2;
		selectPin2 = 3;
		selectPin3 = 4;
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



int IR::readRockSensor(){
  rockSensorValueHighest=0;
  for(channel=1;channel<=8;channel++){
    selectChannel(channel);
	delay(10);
    //read analog value and update store max
      rockSensorValue=analogRead(sensorPin);
	  if(channel == 8) {
		  rockSensorValue += 30;
	  }
      //Serial.println(rockSensorValue);
      //Serial.println(channel);
      //delay(1000);
      if (rockSensorValue>rockSensorValueHighest){
        rockSensorValueHighest=rockSensorValue;
        rockChannel=channel;
      }

	  //Serial.print(channel);
	  //Serial.print(":");
	  //Serial.println(rockSensorValue);
  }


  //check if valid
  if(rockSensorValueHighest>=rockSensorThresholdValue) {
    rockSensorValueValidated=rockSensorValue; //update sensor value
  }else{
    rockChannel=0;
  }

  //Serial.print("(Highest: ");
  //Serial.print(rockChannel);
  //Serial.println(")");

  return(rockChannel);

}
void IR::selectChannel(int channel){

    //select channel
      switch(channel){
        case 1:
          digitalWrite(selectPin1,LOW);
          digitalWrite(selectPin2,LOW);
          digitalWrite(selectPin3,LOW);
          break;
        case 2:
          digitalWrite(selectPin1,LOW);
          digitalWrite(selectPin2,LOW);
          digitalWrite(selectPin3,HIGH);
          break;
        case 3:
          digitalWrite(selectPin1,LOW);
          digitalWrite(selectPin2,HIGH);
          digitalWrite(selectPin3,LOW);
          break;
        case 4:
          digitalWrite(selectPin1,LOW);
          digitalWrite(selectPin2,HIGH);
          digitalWrite(selectPin3,HIGH);
          break;
        case 5:
          digitalWrite(selectPin1,HIGH);
          digitalWrite(selectPin2,LOW);
          digitalWrite(selectPin3,LOW);
          break;
        case 6:
          digitalWrite(selectPin1,HIGH);
          digitalWrite(selectPin2,LOW);
          digitalWrite(selectPin3,HIGH);
          break;
        case 7:
          digitalWrite(selectPin1,HIGH);
          digitalWrite(selectPin2,HIGH);
          digitalWrite(selectPin3,LOW);
          break;
        case 8:
          digitalWrite(selectPin1,HIGH);
          digitalWrite(selectPin2,HIGH);
          digitalWrite(selectPin3,HIGH);
          break;

    }
}

float IR::findAngleRockRobot(int rockChannel){
	float angleRockRobot=0;
	if(rockChannel!=0){
		if(rockChannel!=4 && rockChannel!=5){
			switch(rockChannel){
				case 1:
					angleRockRobot=(-1)*(((40.0f*4.0f)/9.0f)-(20.0f/9.0f));
					break;
				case 2:
					angleRockRobot=(-1)*(((40.0f*3.0f)/9.0f)-(20.0f/9.0f));
					break;
				case 3:
					angleRockRobot=(-1)*(((40.0f*2.0f)/9.0f)-(20.0f/9.0f));
					break;
				case 6:
					angleRockRobot=(1)*(((40.0f*2.0f)/9.0f)-(20.0f/9.0f));
					break;
				case 7:
					angleRockRobot=(1)*(((40.0f*3.0f)/9.0f)-(20.0f/9.0f));
					break;
				case 8:
					angleRockRobot=(1)*(((40.0f*4.0f)/9.0f)-(20.0f/9.0f));
					break;
			}
		} else {
			//balance between two middle sensors, for this you need min and max value of the sensors
			selectChannel(4);
			rockSensor4Value=analogRead(sensorPin);
			selectChannel(5);
			rockSensor5Value=analogRead(sensorPin);
			angleRockRobot=((rockSensor4Value-rockSensor5Value)/(maxRockSensorValue-minRockSensorValue))*(40.0f/9.0f);
			if(angleRockRobot<2){
				angleRockRobot=0;
			}
		}
	} else {
		angleRockRobot=0;
	}

	return angleRockRobot;
}

int IR::alignWithBase(boolean begin){
  int localTreshold = begin ? wallThreshold : rampTreshold;

	detectedChannels=0;
	selectChannel(1);
	delay(100);
	rockSensorValue=analogRead(sensorPin);
  Serial.print("1: ");
    Serial.println(rockSensorValue);
	if (rockSensorValue>localTreshold){
        detectedChannels++;
  } else if(!begin) {
		selectChannel(2);
		delay(100);
		rockSensorValue=analogRead(sensorPin);
    Serial.print("2: ");
    Serial.println(rockSensorValue);
		if (rockSensorValue>localTreshold){
	        detectedChannels++;
	  } else if(!begin) {
      selectChannel(3);
      delay(100);
      rockSensorValue=analogRead(sensorPin);
      Serial.print("3: ");
    Serial.println(rockSensorValue);
      if (rockSensorValue>localTreshold){
            detectedChannels++;
      }
    }
	}
	selectChannel(8);
	delay(100);
	rockSensorValue=analogRead(sensorPin);
  Serial.print("8: ");
    Serial.println(rockSensorValue);
	if (rockSensorValue>localTreshold){
        detectedChannels++;
				detectedChannels++;
  } else if(!begin) {
		selectChannel(7);
		delay(100);
		rockSensorValue=analogRead(sensorPin);
    Serial.print("7: ");
    Serial.println(rockSensorValue);
		if (rockSensorValue>localTreshold){
	        detectedChannels++;
					detectedChannels++;
	  } else if(!begin) {
      selectChannel(6);
      delay(100);
      rockSensorValue=analogRead(sensorPin);
      Serial.print("6: ");
    Serial.println(rockSensorValue);
      if (rockSensorValue>localTreshold){
            detectedChannels++;
            detectedChannels++;
      } 
    }
	}
	return detectedChannels;
}

float IR::readRawLineSensor() {
	float stateLeft = analogRead(sensorPinline1);
	float stateRight = analogRead(sensorPinline2);

	return (stateLeft + stateRight) / 2;
}

int IR::readLineSensor(){
  int stateLeft = analogRead(sensorPinline1);
  int stateRight = analogRead(sensorPinline2);

  if (stateLeft < threshold && stateRight > threshold1){
    return 1;
  }
  //right sensor sees tape
  if (stateRight < threshold1 && stateLeft > threshold){
    return 2;
  }
  //bot see tape
  if(stateRight < threshold1 && stateLeft < threshold){
    return 3;
  }

  return 0;
}
