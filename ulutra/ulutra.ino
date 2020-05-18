/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
#include "Filter.h"
// defines pins numbers
const int trigPin = 3;
const int echoPin = 4;

// defines variables
long duration;
int distance;
int distancef;
ExponentialFilter<long> ADCFilter(15, 0);
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
ADCFilter.Filter(distance);
  distancef = ADCFilter.Current();
// Prints the distance on the Serial Monitor
if(distance < 400)
{
Serial.print("Distance: ");
Serial.println(distance);
}
}
