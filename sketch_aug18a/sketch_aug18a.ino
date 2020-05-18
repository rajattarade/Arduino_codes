#include <Servo.h>

Servo myservo;                                 // create servo object to control a servo
Servo myservo1;                                                // twelve servo objects can be created on most boards
    
int pos = 0;                                     // variable to store the servo position

void setup() {
  myservo.attach(3);
  myservo1.attach(5);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  for (pos = 10; pos <= 60; pos += 1) 
  {       
    myservo.write(pos);                       // tell servo to go to position in variable 'pos'
    delay(50);                                 // waits 15ms for the servo to reach the position
  }
  
{  for (pos = 60; pos >= 10; pos -= 1) 
    {     
    myservo.write(pos);                          // tell servo to go to position in variable 'pos'
    delay(50);                                       // waits 15ms for the servo to reach the position
  }
}
}

 
