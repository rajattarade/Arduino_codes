/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo index;  // create servo object to control a servo
Servo middle;  // create servo object to control a servo
Servo ring;  // create servo object to control a servo
Servo little;  // create servo object to control a servo

// twelve servo objects can be created on most boards

void setup() {
  index.attach(5);  // attaches the servo on pin 9 to the servo object
  middle.attach(6);  // attaches the servo on pin 9 to the servo object
  ring.attach(9);  // attaches the servo on pin 9 to the servo object
  little.attach(10);  // attaches the servo on pin 9 to the servo object
  
  index.write(0);         
  middle.write(0);  
  ring.write(0);  
  little.write(180);
  delay(2000);
}

void loop() {
//  index.write(0);         
//  middle.write(0);  
//  ring.write(0);  
//  little.write(180);
//  while(1);
  
  
   index.write(180);         
   delay(500);     
   middle.write(180);  
   delay(500);
   ring.write(180);  
   delay(500);
   little.write(0);
   delay(500);
   index.write(0);         
   delay(500);     
   middle.write(0);  
   delay(500);
   ring.write(0);  
   delay(500);
   little.write(180);
   delay(500);
  index.write(180);         
  middle.write(180);  
  ring.write(180);  
  little.write(0);
  delay(500);
  index.write(0);         
  middle.write(0);  
  ring.write(0);  
  little.write(180);
  delay(500);   
  middle.write(180);  
  ring.write(180);  
  delay(1000);
  
  index.write(180);         
  middle.write(0);  
  ring.write(0);  
  little.write(0);
  delay(500);  

  index.write(180);         
  middle.write(180);  
  ring.write(180);  
  little.write(0);
 delay(2500);  

 index.write(0);         
  middle.write(0);  
  ring.write(180);  
  little.write(0);
 delay(2500); 

  index.write(0);         
  middle.write(0);  
  ring.write(0);  
  little.write(180);
 delay(2500); 

 index.write(180);         
  middle.write(0);  
  ring.write(180);  
  little.write(0);
 delay(1000); 
  
}

