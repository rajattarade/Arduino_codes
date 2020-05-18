void setup() {
  Serial.begin(19200);               
  Serial.println("CLEARDATA");       
  Serial.println("LABEL,D&T,Volt,Volt1");
}

void loop() {
  Serial.print("DATA,TIME,");
  Serial.print(analogRead(A0));
  Serial.print(",");
  Serial.println(analogRead(A1));
}
