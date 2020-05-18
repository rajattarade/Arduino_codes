#include <Servo.h> 

#define forwardB 3
#define reverseB 4

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to
int motorSpeed = 1500;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
Servo myservo;  

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(forwardB, INPUT_PULLUP);
  pinMode(reverseB, INPUT_PULLUP);
  myservo.attach(9);
}

void loop() {
  // read the analog in value:
  sensorValue = 0;
  for(int i = 0; i < 26 ; i++)
  {
  sensorValue = sensorValue + analogRead(analogInPin);
  // map it to the range of the analog out:
  }
  sensorValue = sensorValue /26;
  outputValue = map(sensorValue, 0, 1023, 0, 500);
  
  if (digitalRead(forwardB) == 0)
  motorSpeed=1500+outputValue;
  else if (digitalRead(reverseB) == 0)
  motorSpeed=1500-outputValue;
  else if (digitalRead(forwardB) == 0 && digitalRead(reverseB) == 0)
  motorSpeed=1500;
  else
  motorSpeed=1500;
  Serial.print("POT = ");
  Serial.print(outputValue);
  Serial.print('\t');
  Serial.print("Speed = ");
  Serial.println(motorSpeed);
  myservo.writeMicroseconds(motorSpeed);
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
