int state;
int state2;

void setup() {
  Serial.begin(9600);
    pinMode(7, INPUT);
}

void loop() {
  state = digitalRead(7);
    if(state2 != state) {
      if(state == HIGH) {
        Serial.println(7);
      }
    }
    state2 = state;  
}
