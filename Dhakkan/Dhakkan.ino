// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup () 
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.print("ASASC");
  if (! rtc.begin()) 
  {
    Serial.print("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) 
  {
    Serial.print("RTC is NOT running!");
  }
   
}

void loop () 
{
    int i = 0;
    int j = 0; 
    DateTime now = rtc.now();

    if(digitalRead(2)==LOW)
    blink();

    for(i = 0 ; i < 24 ; i=i+4)
    {
      if(now.hour() == i)
       {
         if(now.minute()==0 && now.second() == 0)
         {
            digitalWrite(4,HIGH);
            digitalWrite(5,HIGH);
            for(j = 0 ; j < 12 ; j++)
            {
              delay(1000);
            }
            digitalWrite(4,LOW);
            digitalWrite(5,LOW);
         } 
       }  
    }
    Serial.print(now.hour());
    Serial.print(':');
    Serial.print(now.minute());
    Serial.print(':');
    Serial.print(now.second());
    Serial.println("   ");
}

void blink() {
  rtc.adjust(DateTime(1971, 12, 17, 0, 0, 0));// to set the time manualy 
 }
