// this sketch cycles three servos at different rates 

#include <ServoTimer2.h>  // the servo library

// define the pins for the servos
#define rollPin  10

ServoTimer2 servoRoll;    // declare variables for up to eight servos

void setup() {
  servoRoll.attach(rollPin);     // attach a pin to the servos and they will start pulsing
}


void loop()
{ 
   servoRoll.write(2000);
   delay(500);   
   servoRoll.write(1000);
   delay(500);   
   
}
