#include <Servo.h>

Servo indexF;
Servo middleF;
Servo ringF;
Servo littleF;
Servo thumbC;
Servo thumbR;
 


void setup() {
  thumbR.attach(11); //analog pin 0
  //thumbR.setMaximumPulse(1500);
  //servo1.setMinimumPulse(700);

 indexF.attach(3);
 middleF.attach(5);
 ringF.attach(6);
 littleF.attach(9);
 thumbC.attach(10);
  Serial.begin(19200);
  Serial.println("Ready");
  indexF.write(0);
  middleF.write(0);
  ringF.write(0);
  littleF.write(180);
  thumbC.write(0);
  thumbR.write(90);
  delay(2000);
}

void loop()
{
 indexF.write(180);
 middleF.write(180);
 ringF.write(180);
 littleF.write(0);
 
 delay(2000);
  indexF.write(0);
  middleF.write(0);
  ringF.write(0);
  littleF.write(180);

  delay(2000);
} 
