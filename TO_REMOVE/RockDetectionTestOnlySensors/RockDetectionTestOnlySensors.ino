#include <IR.h>
#include <Motion.h>
#include <Encoder.h>
#include <Math.h>

IR ir(1);
int tt = 0;
int sensorValueMeasured=0;
int sensorPin=A0;
void setup(){
  ir.setup();
  Serial.begin(9600);
  }
void loop(){
  
  ir.selectChannel(tt);
  sensorValueMeasured=analogRead(sensorPin);
  
  for(int i=0; i<30; i++){
    Serial.println(sensorValueMeasured);
    delay(10);
  } 
  
  //delay(100);
  tt++;
  //Serial.println(tt);
  
  if(tt>7){
      tt=0;
    }
   
}

  
