#include <LiquidCrystal.h>

int val;
int encoder0PinA = 4;
int encoder0PinB = 5;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;
int setPoint = -6;
int input = 0;
int positioning = 0;

void setup() {
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  Serial.begin (115200);
}

void loop() {

  n = digitalRead(encoder0PinA);
  if (n != encoder0PinALast) {
    if (digitalRead(encoder0PinB) != n) {
      encoder0Pos--;
      //delay(1);
    } else {
      encoder0Pos++;
      //delay(1);
    }
    Serial.print (encoder0Pos);
    Serial.println();
  }
  encoder0PinALast = n;
}

