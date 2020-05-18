#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 7, 6, 3, 5);
#define v_Pin A0
#define i1_Pin A1
#define i2_Pin A2
#define i3_Pin A3




void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  pinMode(r1_Pin, OUTPUT);
  pinMode(r2_Pin, OUTPUT);
  pinMode(r3_Pin, OUTPUT);
  digitalWrite(r1_Pin, HIGH);
  digitalWrite(r2_Pin, HIGH);
  digitalWrite(r3_Pin, HIGH);
  lcd.print("Loading...");
  delay(2000); 
}

void loop() {
  float v=0;
  float i1=0;
  float i2=0;
  float i3=0;
  v = analogRead(v_Pin)/3.35; 
  i1 = analogRead(i1_Pin)/25.625;
  i2 = analogRead(i2_Pin)/25.625;
  i3 = analogRead(i3_Pin)/10.25;

  
  if(v<200)
  {
  digitalWrite(r1_Pin, LOW);
  digitalWrite(r2_Pin, LOW);
  digitalWrite(r3_Pin, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LOW VOLTAGE");
  while(1);
  }
  if(i1>1)
  digitalWrite(r1_Pin, LOW);
  if(i2>3)
  digitalWrite(r2_Pin, LOW);
  if(i3>5)
  digitalWrite(r3_Pin, LOW);
    
  lcd.setCursor(0, 0);
  lcd.print("Voltage :");
  lcd.print(v);
  lcd.print(" V  ");
  lcd.setCursor(0, 1);
  lcd.print("Line 1 :");
  lcd.print(i1);
  lcd.print(" A ");
  lcd.setCursor(0, 2);
  lcd.print("Line 2 :");
  lcd.print(i2);
  lcd.print(" A  ");
  lcd.setCursor(0, 3);
  lcd.print("Line 3 :");
  lcd.print(i3);
  lcd.print(" A  ");
}

