#include <LiquidCrystal.h>
#include "EmonLib.h"             // Include Emon Library
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;    //For SPI communication with SD card

EnergyMonitor emon1;             // Create an instance
EnergyMonitor emon2;             // Create an instance
EnergyMonitor emon3;             // Create an instance

#define r1_Pin A5   //Relay 1
#define r2_Pin A4   //Relay 2
#define r3_Pin 2    //Relay 3
int count = 0;      //Serial counter

LiquidCrystal lcd(9, 8, 7, 6, 3, 5); //LCD pins defined
void setup()
{  
  //Code here will run once
  lcd.begin(20, 4);
  pinMode(r1_Pin, OUTPUT);    //
  pinMode(r2_Pin, OUTPUT);
  pinMode(10, INPUT);
  pinMode(r3_Pin, OUTPUT);
  digitalWrite(r1_Pin, HIGH);
  digitalWrite(r2_Pin, HIGH);
  digitalWrite(r3_Pin, HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing SD card");
  if (!SD.begin(chipSelect)) {
    lcd.setCursor(0, 1);
    lcd.print("Card failed,");
    lcd.setCursor(0, 2);
    lcd.print("or not present");    
     delay(1000);
    // while (1);
  }
  else
  {
  lcd.setCursor(0, 1);
  lcd.println("card initialized.");
  delay(1000);
  }
  emon1.voltage(0, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(3, 18.11);       // Current: input pin, calibration.
  emon2.current(2, 18.11);       // Current: input pin, calibration.
  emon3.current(1, 18.11);       // Current: input pin, calibration.
  for(int i=0; i<2; i++)
  {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Please wait");
   lcd.setCursor(0, 1);
   lcd.print("Calibrating");
   emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
   emon2.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
   emon3.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
   lcd.setCursor(0, 1);
   lcd.print("Calibrating.");
   emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
   emon2.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
   emon3.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
   lcd.setCursor(0, 1);
   lcd.print("Calibrating..");
   emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
   emon2.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
   emon3.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
   lcd.setCursor(0, 1);
   lcd.print("Calibrating...");
  }
  digitalWrite(r1_Pin, LOW);
  digitalWrite(r2_Pin, LOW);
  digitalWrite(r3_Pin, LOW);
    delay(1000);
}

void loop()
{
  int r=0;
  digitalWrite(r1_Pin, LOW);
  digitalWrite(r2_Pin, LOW);
  digitalWrite(r3_Pin, LOW);
  for(r=0;r<10;r++)
  delay(1000);
  digitalWrite(r1_Pin, LOW);
  digitalWrite(r2_Pin, LOW);
  digitalWrite(r3_Pin, HIGH);
  for(r=0;r<10;r++)
  delay(1000);
  digitalWrite(r1_Pin, LOW);
  digitalWrite(r2_Pin, HIGH);
  digitalWrite(r3_Pin, HIGH);
  for(r=0;r<10;r++)
  delay(1000);
  digitalWrite(r1_Pin, HIGH);
  digitalWrite(r2_Pin, HIGH);
  digitalWrite(r3_Pin, HIGH);
  while(1);
  /*
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon2.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon3.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out

  String dataString = "";
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms1            = emon1.Irms;             //extract Irms into Variable
  float Irms2            = emon2.Irms;             //extract Irms into Variable
  float Irms3            = emon3.Irms;             //extract Irms into Variable

  if(supplyVoltage<200)
  {
  digitalWrite(r1_Pin, HIGH);
  digitalWrite(r2_Pin, HIGH);
  digitalWrite(r3_Pin, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LOW VOLTAGE");
  lcd.setCursor(0, 1);
  lcd.print("Please Reset");
  while(1);
  }
  lcd.clear();  

  if(Irms1>0.45)
  {
  digitalWrite(r1_Pin, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Line 1 : FAULTY");
  }
  else
  {
   lcd.setCursor(0, 1);
   lcd.print("Line 1 :");
   lcd.print(Irms1);
   lcd.print(" A ");
  }
  
  if(Irms2>0.47)
  {
  digitalWrite(r2_Pin, HIGH);
  lcd.setCursor(0, 2);
  lcd.print("Line 2 : FAULTY");
  }
   else
  {
   lcd.setCursor(0, 2);
   lcd.print("Line 2 :");
   lcd.print(Irms2);
   lcd.print(" A  ");
  }
  
  if(Irms3>0.4)
  {
  digitalWrite(r3_Pin, HIGH);
  lcd.setCursor(0, 3);
  lcd.print("Line 3 : FAULTY");
  }
  else
  {
  lcd.setCursor(0, 3);
  lcd.print("Line 3 :");
  lcd.print(Irms3);
  lcd.print(" A  ");
  }
  

  lcd.setCursor(0, 0);
  lcd.print("Voltage :");
  lcd.print(supplyVoltage);
  lcd.print(" V  ");

  dataString = count;
  dataString += String(",");
  dataString += String(supplyVoltage);
  dataString += String(",");
  dataString += String(Irms1);
  dataString += String(",");
  dataString += String(Irms2);
  dataString += String(",");
  dataString += String(Irms3);

  if(digitalRead(10))
  {
   File  dataFile = SD.open("DATALOG.CSV", FILE_WRITE);
    if (dataFile)
    {
    dataFile.println(dataString);
    dataFile.close();
    lcd.setCursor(19, 4);
    lcd.print("L");
    count++;
    }
    else 
    {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("error opening");
    lcd.setCursor(0, 1);
    lcd.print("SD card file");
    }
  }*/
}
