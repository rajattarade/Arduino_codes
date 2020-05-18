#include <Servo.h>
#include "Filter.h"
Servo myservo[6];  // create servo object to control a servo
char ch = '0';
boolean state = 0;
int startup=0;

//Global Variables
ExponentialFilter<long> ADCFilter1(110, 0);
ExponentialFilter<long> ADCFilter2(110, 0);

void setup() {
  Serial.begin(115200);
  myservo[0].attach(3);  // attaches the servo on pin 9 to the servo object
  myservo[1].attach(5);  // attaches the servo on pin 9 to the servo object
  myservo[2].attach(6);  // attaches the servo on pin 9 to the servo object
  myservo[3].attach(9);  // attaches the servo on pin 9 to the servo object
  myservo[4].attach(10);  // attaches the servo on pin 9 to the servo object
  myservo[5].attach(11);  // attaches the servo on pin 9 to the servo object

  myservo[0].write(0);
  myservo[1].write(0);
  myservo[2].write(0);
  myservo[3].write(180);
  myservo[4].write(0);
  myservo[5].write(90);

}

void loop() {
  int filtered1 = 0;
  int filtered2 = 0;
//  
//  while(1)
//  {
//  ADCFilter1.Filter(analogRead(A0));
//  filtered1 = ADCFilter1.Current();
//  ADCFilter2.Filter(analogRead(A1));
//  filtered2 = ADCFilter2.Current();
//  Serial.println(filtered1);
//  if(filtered1>80)
//  break;
//  }
//  
//    if (state)
//    {
//      ServoWrite(0, 180, 1, 180, 2, 180, 3, 0, 4, 180, 5, 90);
//      state = 0;
//    }
//    else
//    {
//      ServoWrite(0, 0, 1, 0, 2, 0, 3, 180, 4, 0, 5, 90);
//      state = 1;
//    }

  if (Serial.available())
  {
    ch = Serial.read();
  }
  Serial.println(ch);
  if (ch == 'G')
    ServoWrite(0, 180, 1, 180, 2, 180, 3, 0, 4, 180, 5, 90);
  if (ch == 'R')
    ServoWrite(0, 0, 1, 0, 2, 0, 3, 180, 4, 0, 5, 90);
  if (ch == 'C')
    ServoWrite(0, 180, 1, 0, 2, 180, 3, 0, 4, 180, 5, 90);
  if (ch == '1')
    ServoWrite(0, 0, 1, 180, 2, 180, 3, 0, 4, 180, 5, 90);
  if (ch == '2')
    ServoWrite(0, 0, 1, 0, 2, 180, 3, 0, 4, 180, 5, 90);
  if (ch == '3')
    ServoWrite(0, 0, 1, 0, 2, 0, 3, 0, 4, 180, 5, 90);
  if (ch == '4')
    ServoWrite(0, 0, 1, 0, 2, 0, 3, 180, 4, 180, 5, 90);
  if (ch == '5')
    ServoWrite(0, 0, 1, 0, 2, 0, 3, 180, 4, 0, 5, 90);
}

void ServoWrite(int n1, int a1, int n2, int a2, int n3, int a3, int n4, int a4, int n5, int a5, int n6, int a6)
{
  int i1 = myservo[n1].read();
  int i2 = myservo[n2].read();
  int i3 = myservo[n3].read();
  int i4 = myservo[n4].read();
  int i5 = myservo[n5].read();
  int i6 = myservo[n6].read();

  while (i1 != a1 || i2 != a2 || i3 != a3 || i4 != a4 || i5 != a5 || i6 != a6)
  {
    if (i1 < a1)
      i1++;
    if (i1 > a1)
      i1--;

    if (i2 < a2)
      i2++;
    if (i2 > a2)
      i2--;

    if (i3 < a3)
      i3++;
    if (i3 > a3)
      i3--;

    if (i4 < a4)
      i4++;
    if (i4 > a4)
      i4--;

    if (i5 < a5)
      i5 = i5 + 2;
    if (i5 > a5)
      i5--;

    if (i6 < a6)
      i6++;
    if (i6 > a6)
      i6--;

    myservo[n1].write(i1);
    myservo[n2].write(i2);
    myservo[n3].write(i3);
    myservo[n4].write(i4);
    myservo[n5].write(i5);
    myservo[n6].write(i6);
    delay(6);
  }
}

