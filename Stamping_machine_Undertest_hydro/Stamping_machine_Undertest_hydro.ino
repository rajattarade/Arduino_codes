#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "OneButton.h"

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int val;

#define encoder0PinA 5
#define encoder0PinB 4
//#define encoderswitch 6

#define valveSwitch 2
#define releaseSwitch 3
#define pressureSwitch 12

#define selector 7
#define runButton 8
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 2000

int mode = 0;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;
int setPoint = -6;
int input = 0;
int positioning = 0;
int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int Fnumber = 0;

byte cPosition = 0;
boolean mMode = 0;
BasicStepperDriver stepper(6000, 10, 9, 11);
OneButton encoderswitch(6, true);

void setup() {
  encoderswitch.attachClick(cursorUpdate);
  encoderswitch.attachDoubleClick(ManualMode);
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);

  pinMode (pressureSwitch, INPUT_PULLUP);
  pinMode (selector, INPUT);
  pinMode (runButton, INPUT_PULLUP);
  pinMode (valveSwitch, OUTPUT);
  pinMode (releaseSwitch, OUTPUT);

  digitalWrite (valveSwitch, HIGH);
  digitalWrite (releaseSwitch, HIGH);
  
  stepper.begin(4, 1);
  Serial.begin(115200);
  //Run(250);
  //stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
  Wire.begin();
  Wire.beginTransmission(0x27);

  lcd.begin(16, 2); // initialize the lcd

  lcd.setBacklight(255);
  lcd.home();
  lcd.clear();
  lcd.cursor();
  lcd.print("Enter Angle : ");
  lcd.setCursor(cPosition, 1);
  lcd.print("000");
  encoder0PinALast = digitalRead(encoder0PinA);

}

void loop() {
  encoderswitch.tick();
  Serial.print(digit1);
  Serial.print(" ");
  Serial.print(digit2);
  Serial.print(" ");
  Serial.print(digit3);
  Serial.print(" ");
  Serial.println(encoder0Pos);

  stepper.disable();

  if (digitalRead(selector) && mode == 1)
  {
    lcd.home();
    lcd.print("Enter Angle : ");
    mode = 0;
  }
  if (!digitalRead(selector) && mode == 0)
  {
    lcd.home();
    lcd.print("Enter Steps : ");
    mode = 1;
  }

  n = digitalRead(encoder0PinA);
  if (n != encoder0PinALast)
  {
    if (digitalRead(encoder0PinB) != n)
    {
      encoder0Pos = encoder0Pos - 1;
      if (encoder0Pos < 0)
        encoder0Pos = 0;
    }
    else
    {
      encoder0Pos = encoder0Pos + 1;
      if (encoder0Pos > 18)
        encoder0Pos = 18;
    }
    if (cPosition == 0 && (encoder0Pos % 2) == 0)
      digit1 = encoder0Pos / 2;
    if (cPosition == 1 && (encoder0Pos % 2) == 0)
      digit2 = encoder0Pos / 2;
    if (cPosition == 2 && (encoder0Pos % 2) == 0)
      digit3 = encoder0Pos / 2;

    LCDupdate();
  }
  encoder0PinALast = n;


  if (digitalRead(runButton) == 0)
  {
    delay(150);
    if (digitalRead(runButton) == 0)
    {
      float i = 0;
      if (mode == 0)
      {
        //Angle

        i = 6000 * (float(Fnumber) / 360);
        Serial.print("I : ");
        Serial.println(i);
      }
      if (mode == 1)
      {
        //Steps
        Serial.print("Number : ");
        Serial.println(Fnumber);

        i = float(6000) / float(Fnumber);
        Serial.print("I : ");
        Serial.println(i);
      }
      float j = 0;
      //Run(250);
      while (j < (6000 - i))
      {
        j = i + j;
        Serial.println(j);
        digitalWrite (valveSwitch, LOW);
        while(digitalRead(pressureSwitch));
        delay(100);
        while(digitalRead(pressureSwitch));
        digitalWrite (valveSwitch, HIGH);
        delay(200);
        digitalWrite (releaseSwitch, LOW);
        delay(1500);
        digitalWrite (releaseSwitch, HIGH);
        delay(200);
        Run(i);
      }
      Serial.println(6000 - j);
      Run(6000 - j);
    }
  }
}

void LCDupdate()
{
  lcd.setCursor(cPosition, 1);
  if (cPosition == 0)
    lcd.print(digit1);
  if (cPosition == 1)
    lcd.print(digit2);
  if (cPosition == 2)
    lcd.print(digit3);
  delay(5);
  Fnumber = (digit1 * 100) + (digit2 * 10) + digit3;
}

void cursorUpdate()
{
  cPosition++;
  if (cPosition > 2)
    cPosition = 0;
  if (cPosition == 0)
    encoder0Pos = digit1 * 2;
  if (cPosition == 1)
    encoder0Pos = digit2 * 2;
  if (cPosition == 2)
    encoder0Pos = digit3 * 2;
  LCDupdate();
}

void Run(int steps)
{
  stepper.enable();
  stepper.move(steps);
  Serial.println(steps);
  stepper.disable();
}

void ManualMode()
{
  int runCount = 0;
  lcd.clear();
  lcd.home();
  lcd.print("Manual Mode : ");
  while (digitalRead(6))
  {
    if (digitalRead(runButton) == 0)
    {
      delay(150);
      if (digitalRead(runButton) == 0)
      {
        digitalWrite (valveSwitch, LOW);
        while(digitalRead(pressureSwitch));
        delay(100);
        while(digitalRead(pressureSwitch));
        digitalWrite (valveSwitch, HIGH);
        delay(200);
        digitalWrite (releaseSwitch, LOW);
        delay(1500);
        digitalWrite (releaseSwitch, HIGH);
        delay(200);
      }
    } 
        n = digitalRead(encoder0PinA);
        if (n != encoder0PinALast)
        {
          if (digitalRead(encoder0PinB) != n)
          {
            //++
            runCount = runCount + 1;
            if (runCount > 1)
            {
              Run(16);
              runCount = 0;
            }
          }
          else
          {
            runCount = runCount - 1;
            if (runCount < -1)
            {
              Run(-16);
              runCount = 0;
            }
          }
        }
        encoder0PinALast = n;
      }

      if (mode == 0)
      {
        lcd.home();
        lcd.print("Enter Angle : ");
      }
      else
      {
        lcd.home();
        lcd.print("Enter Steps : ");
      }
      lcd.setCursor(0, 1);
      lcd.print(digit1);
      lcd.setCursor(1, 1);
      lcd.print(digit2);
      lcd.setCursor(2, 1);
      lcd.print(digit3);
    }
