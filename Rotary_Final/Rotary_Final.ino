#include <LiquidCrystal.h>

int val;
int encoder0PinA = 4;
int encoder0PinB = 5;
int encoder0Pos = -6;
int encoder0PinALast = LOW;
int n = LOW;
int setPoint = -6;
int input = 0;
int positioning = 0;
LiquidCrystal lcd(8, 9, 13, 12, 11, 10);

#define enable A1
#define motorPin0 2
#define motorPin1 3

void setup() {
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  pinMode (motorPin0, OUTPUT);
  pinMode (motorPin1, OUTPUT);
  pinMode (enable, INPUT);
  Serial.begin (9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("Count : ");
  lcd.print(encoder0Pos+6);
}

void loop() {
  lcd.clear();
  input = analogRead(A0);
  if (input >= 1000)
  input = 1000;
  if(input <= 40)
  input = 40;
input=map(input, 40,1000,0,12);
input=map(input, 0,12,40,1000);

  lcd.setCursor(0, 0);
  lcd.print("I: ");
  lcd.print(map(input, 40, 1000, 0, 180));
  lcd.setCursor(10, 0);
  lcd.print("C: ");
  lcd.print(map(encoder0Pos, -6, 6, 0, 180));
  lcd.setCursor(0, 1);
  lcd.print("Count : ");
  lcd.print(setPoint - encoder0Pos);
  delay(6);
  Serial.print("Input Angle : ");
  Serial.print(map(input, 40, 1000, 0, 180));
  Serial.print("\t\t\t\t\t\t\t");
  setPoint = map(input,30 ,1000, -6, 6);
  Serial.print("Current Angle : ");
  Serial.print(map(encoder0Pos, -6, 6, 0, 180));
  //Serial.print(encoder0Pos);
  Serial.println("\t");
  
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
  if(digitalRead(enable) || positioning == 1)
  {
   delay(10);
  if(setPoint < encoder0Pos)
  {
   positioning = 1;
   digitalWrite(motorPin0, HIGH);
   digitalWrite(motorPin1, LOW);
   delay(3);
  }
  if(setPoint > encoder0Pos)
  {
   positioning = 1;
   digitalWrite(motorPin0, LOW);
   digitalWrite(motorPin1, HIGH);
   delay(3);
  }
  if(setPoint == encoder0Pos)
  {
   positioning = 0;
   digitalWrite(motorPin0, LOW);
   digitalWrite(motorPin1, LOW);
  }
   digitalWrite(motorPin0, LOW);
   digitalWrite(motorPin1, LOW);
   delay(3);
  }
}

