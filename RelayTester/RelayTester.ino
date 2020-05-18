/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald

  modified 2 Sep 2016
  by Arturo Guadalupi

  modified 8 Sep 2016
  by Colby Newman
*/

int c = 1;
int i = 2;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  for (int j = 2; j < 10; j++)
    pinMode(j, OUTPUT);
  for (int j = 2; j < 10; j++)
    digitalWrite(j, HIGH);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
for(i=3;i<11;i++)
{
  for (c = 2; c < i; c++)
  {
    digitalWrite(c, LOW);
  }
  delay(500);
  for (c = 2; c < i; c++)
  {
    digitalWrite(c, HIGH);
  }
  delay(500);
}
for(i=3;i<11;i++)
{
  for (c = i; c > 1; c--)
  {
    digitalWrite(c, HIGH);
  }
  delay(500);
  for (c = i; c > 1; c--)
  {
    digitalWrite(c, LOW);
  }
  delay(500);
}
}
