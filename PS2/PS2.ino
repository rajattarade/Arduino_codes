#include <SmartElexPs2Shield.h>
SmartElexPs2Shield ps(10,11);
void setup()
{
  ps.begin(9600);
  Serial.begin(9600);
  for(int i=0;i<5;i++)
  {
    ps.SetController(ps.AnalogMode);
    delay(20);
  }
  ps.VibrateMotors(0,255);
  ps.ReadControllerButtons();
  delay(3000);
  ps.VibrateMotors(0,0);
 
  // put your setup code here, to run once:
}
void loop() 
{
  
  ps.ReadControllerButtons();
  
  delay(20);


  Serial.print(ps.RIGHT_X_AXIS);Serial.print(" ");
  Serial.print(ps.RIGHT_Y_AXIS);Serial.print(" ");
  Serial.print(ps.LEFT_X_AXIS);Serial.print(" ");
  Serial.print(ps.LEFT_Y_AXIS);Serial.print("    ");
  
  Serial.print(ps.L1);
  Serial.print(ps.R1);Serial.println("   ");
  // put your main code here, to run repeatedly: 
}
