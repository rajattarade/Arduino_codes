#include <Servo.h> 
#include <math.h>

Servo myservo; 
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

float sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  Serial.begin(9600);
  Serial.println("Redy");
  myservo.attach(9);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  sensorValue = sensorValue - 508;
  sensorValue = sensorValue / 25;
  long temp = (sensorValue*sensorValue*sensorValue)+1500;
  if(temp<1000)
  temp = 1000;
  if(temp>2000)
  temp = 2000;
  
  constrain(temp, 1000, 2000);
  Serial.print("temp = ");
  Serial.print(temp);
  

  // change the analog out value:
  myservo.writeMicroseconds(temp);
  // print the results to the Serial Monitor:
  Serial.print("\t sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
