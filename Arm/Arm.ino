#include "AnaTechArm.h"
#define USMIN  500 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600

Anatecharm RobotArm1;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  delay(10);
}

void loop()
{
  Serial.println("8 channel Servo test!");
  Serial.println(RobotArm1.Babaduk(10));
  //pitch(50);
  //roll(50);
  //gripper(0);
  //elbow(100);
  //shoulder(45);
  //base(50);
//  for (uint16_t microsec = 0; microsec < 100; microsec++)
//  {
//    RobotArm1.elbow(microsec);
//    delay(5);
//  }
//  
//  delay(1000);
//  
//  for (uint16_t microsec = 100; microsec > 0; microsec--) 
//  {
//    RobotArm1.elbow(microsec);
//    delay(5);
//  }
  
  //delay(1000);
}

