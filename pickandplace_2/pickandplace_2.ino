#include <AnaTechArm.h>

AnaTechArm Robot;

void setup()
{
  Serial.begin(9600);
  Robot.begin();
  delay(2000);
}

void loop()
{
    Robot.base(0);
    delay(1000);
    Robot.shoulder(0);
    delay(1000);
    Robot.gripper(100);
    delay(1000);
    Robot.elbow(20); 
    delay(1000);
    Robot.gripper(0);
    delay(1000);
    Robot.shoulder(60);
    Robot.elbow(10); 
    delay(1000);
    Robot.base(100);
    delay(1000);
    Robot.pitch(15);
    delay(1000);
    Robot.shoulder(60);
    delay(1000);
    Robot.gripper(100);
    delay(1000);
    //------------------/////----------////-
    Robot.gripper(0);
    delay(1000);
    Robot.pitch(50);
    delay(1000);
    Robot.elbow(50); 
    delay(1000);
    Robot.base(0);
    delay(1000);
    Robot.shoulder(0);
    Robot.elbow(20); 
    delay(1000);
    Robot.gripper(100);
    delay(1000);
}

