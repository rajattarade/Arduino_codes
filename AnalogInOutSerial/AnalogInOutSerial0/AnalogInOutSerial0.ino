void setup() {
   Serial.begin(9600);
   pinMode(2, INPUT_PULLUP);
   pinMode(3, INPUT_PULLUP);
   pinMode(4, INPUT_PULLUP);
   pinMode(5, INPUT_PULLUP);
   pinMode(6, INPUT_PULLUP);
   pinMode(7, INPUT_PULLUP);
}

void loop() {
  Serial.print(analogRead(A2));
  Serial.print("\t");
  Serial.print(analogRead(A3));
  Serial.print("\t");
  Serial.print(analogRead(A4));
  Serial.print("\t");
  Serial.print(analogRead(A5));
  Serial.print("\t");
  Serial.print(analogRead(A6));
  Serial.print("\t");
  Serial.print(analogRead(A7));
  Serial.print("\t");
  Serial.print(digitalRead(2));
  Serial.print("\t");
  Serial.print(digitalRead(3));
  Serial.print("\t");
  Serial.print(digitalRead(4));
  Serial.print("\t");
  Serial.print(digitalRead(5));
  Serial.print("\t");
  Serial.print(digitalRead(6));
  Serial.print("\t");
  Serial.print(digitalRead(7));
  Serial.println("\t");
   
   
  delay(2);
}
