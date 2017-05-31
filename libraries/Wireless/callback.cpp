void serialEvent() {
  Wireless wireless(5,6);
  String buffer = Serial.readString();
  if(buffer.indexOf('@') == -1) {
    wireless.store(Serial.readString());
  }
}
