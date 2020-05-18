/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */
/*working variables*/
unsigned long lastTime;
double Input, Output, Setpoint;
double errSum, lastErr;
double kp=0.1, ki=0.0001, kd=200;

#include <Stepper.h>


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(200, 9, 8, 11, 10);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to



int error = 0;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int setValue = 50;
void setup() {
 // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
    myStepper.setSpeed(6);
}

void loop() {
  double error=0;
   if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
   // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 100);
  
   /*How long since we last calculated*/
   unsigned long now = millis();
   double timeChange = (double)(now - lastTime);
  
   /*Compute all the working error variables*/
   for(int i=0; i<10000; i++)
   {
   error = setValue - outputValue + error;
   }
   error = (error/10000);
   errSum += (error * timeChange);
   double dErr = (error - lastErr) / timeChange;

   /*Compute PID Output*/
   Output = kp * error + ki * errSum + kd * dErr;
   Output = constrain(Output, -1, 1);
   Output = int(Output);

   /*Remember some variables for next time*/
   lastErr = error;
   lastTime = now;
  Serial.print("\t P = ");
  Serial.print(kp * error);
  Serial.print("\t I = ");
  Serial.print(ki * errSum);
  Serial.print("\t D = ");
  Serial.print(kd * dErr);
  Serial.print("\t error = ");
  Serial.print(error);
  Serial.print("\t Output = ");
  Serial.print(kp * error + ki * errSum + kd * dErr);
  Serial.print("\t control = ");
  Serial.println(Output);

  myStepper.step(-Output);  // turn the LED on (HIGH is the voltage level)                    // wait for a second
  delay(5);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    setValue = inputString.toInt();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      
    }
  }
}
