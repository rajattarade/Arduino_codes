#include <Servo.h>

Servo myservo[6];  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo[0].attach(3); 
  myservo[1].attach(5);  
  myservo[2].attach(6);  
  myservo[3].attach(9);  
  myservo[4].attach(10); 
  myservo[5].attach(11);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    for(int i=0; i < 6; i++)
    myservo[i].write(pos);
    delay(15);                       
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
   for(int i=0; i < 6; i++)
    myservo[i].write(pos);
    delay(15);                       
  }
}
