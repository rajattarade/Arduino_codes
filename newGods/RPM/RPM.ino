 volatile byte half_revolutions;
 unsigned int rpm;
 unsigned long timeold;
 unsigned int mgear=0;
 unsigned int cgear=0;
 
 
 void setup()
 {
   Serial.begin(9600);
   attachInterrupt(0, rpm_fun, RISING);
   half_revolutions = 0;
   rpm = 0;
   timeold = 0;
 }
 void loop()
 {
   if (half_revolutions >= 100) { 
     //Update RPM every 20 counts, increase this for better RPM resolution,
     //decrease for faster update
     rpm = 30*1000/(millis() - timeold)*half_revolutions;
     timeold = millis();
     half_revolutions = 0;
   }
   
   if(((millis()-timeold)>4000) || rpm>4500)
   rpm=0;
   
   if(rpm>=0 && rpm<1500)
   mgear=1;

   if(rpm>1500 && rpm<2125)
   mgear=2;

   if(rpm>2125 && rpm<2750)
   mgear=3;

   if(rpm>2750 && rpm<3375)
   mgear=4;

   if(rpm>3375)
   mgear=5;
 
 if(cgear!=mgear)
  {
   
   if(cgear<mgear)
    {
      cgear++;
      delay(1000);
    }
    if(cgear<mgear)
    {
      cgear--;
      delay(1000);
    }    
  }
  else
  {
    Serial.println(cgear);  
  }
}
 
 void rpm_fun()
 {
   half_revolutions++;
 }

 

 
