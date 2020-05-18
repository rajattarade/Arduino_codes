#include <Servo.h> 


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
  outputValue = map(sensorValue,0,1023,1200,1800);

  // change the analog out value:
  myservo.writeMicroseconds(outputValue);
  // print the results to the Serial Monitor:
  Serial.print("\t sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
