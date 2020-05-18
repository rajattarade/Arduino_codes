#include <Servo.h>

Servo updown;
Servo leftright;
int ud = 70;
int lr = 0;
int thr = 400;
int topleft;
int topright;
int downleft;
int downright;
String pos;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  updown.attach(9);
  leftright.attach(10);
}

void loop() {

  topleft = analogRead(A3);//a3
  topright = analogRead(A2);//a2
  downleft = analogRead(A0);//a0
  downright = analogRead(A1);//a1
  // tell servo to go to position in variable 'pos'
  leftright.write(lr);
  updown.write(ud);


  if (topleft > thr)
  {
    Serial.print(topleft);
    Serial.print("\t");
  }
  else
  {
    Serial.print(topleft);
    Serial.print("\t");
    if (downleft < thr)
    {
      lr = lr + 1;
      if (lr > 180)
        lr = 180;
    }
    if (topright < thr)
    {
      ud = ud + 1;
      if (ud > 70)
        ud = 70;
    }
  }

  if (topright > thr)
  {
    Serial.print(topright);
    Serial.print("\t");
  }
  else
  {
    Serial.print(topright);
    Serial.print("\t");
    if (downright < thr)
    {
      lr = lr - 1;
      if (lr < 0)
        lr = 0;
    }
    if (topleft < thr)
    {
      ud = ud + 1;
      if (ud > 70)
        ud = 70;
    }
  }

  if (downright > thr)
  {
    Serial.print(downright);
    Serial.print("\t");
  }
  else
  {
    Serial.print(downright);
    Serial.print("\t");
    if (downleft < thr)
    {
      ud = ud - 1;
      if (ud < 0)
      ud = 0;
    }
    if (topleft < thr)
    {
      lr = lr + 1;
      if (lr > 180)
      lr = 180;
    }
  }

  if (downleft > thr)
  {
    Serial.print(downleft);
    Serial.print("\t");
  }
  else
  {
    Serial.print(downleft);
    Serial.print("\t");
    if (downright < thr)
    {
      ud = ud - 1;
      if (ud < 0)
      ud = 0;
    }
    if (topleft < thr)
    {
      lr = lr + 1;
      if (lr > 180)
      lr = 180;
    }
  }

  Serial.print("\t");
  Serial.print(lr);
  Serial.print("\t");
  Serial.print(ud);

  Serial.println();

  delay(20);
}
