
void setup() {

}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
int buttonState0 = digitalRead(pushButton0);
int buttonState1 = digitalRead(pushButton1);
int buttonState2 = digitalRead(pushButton2);
int buttonState3 = digitalRead(pushButton3);
int buttonState4 = digitalRead(pushButton4);
int buttonState5 = digitalRead(pushButton5);
int buttonState6 = digitalRead(pushButton6);
int buttonState7 = digitalRead(pushButton7);
int buttonState8 = digitalRead(pushButton8);
int buttonState9 = digitalRead(pushButton9);
int buttonState10 = digitalRead(pushButton10);

  // print out the state of the button:
  Serial.print(buttonState0);
  Serial.print("\t");
  Serial.print(buttonState1);
  Serial.print("\t");
  Serial.print(buttonState2);
  Serial.print("\t");
  Serial.print(buttonState3);
  Serial.print("\t");
  Serial.print(buttonState4);
  Serial.print("\t");
  Serial.print(buttonState5);
  Serial.print("\t");
  Serial.print(buttonState6);
  Serial.print("\t");
  Serial.print(buttonState7);
  Serial.print("\t");
  Serial.print(buttonState8);
  Serial.print("\t");
  Serial.print(buttonState9);
  Serial.print("\t");
  Serial.println(buttonState10);
  delay(1);        // delay in between reads for stability
}



