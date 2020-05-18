// Include librarys
#include <SdFat.h>
#include <SdFatUtil.h>
#include <Wire.h>  // i2C/1-wire library
#include "RTClib.h"
#include <LiquidCrystal.h>
#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"


FPS_GT511C3 fps(A0, 2);
LiquidCrystal lcd(8, 9, 3, 5, 6, 7);
RTC_DS1307 RTC;
// store error strings in flash to save RAM
#define error(s) sd.errorHalt_P(PSTR(s))
DateTime time;

int succesRead = 500;
// Declaration of the functions
const int chipSelect = 4;
SdFat sd;
SdFile myFile;

// buffer to format data - makes it eaiser to echo to Serial
int getID();  // read tag
void StoreData(int rollNum);  // store data to microSD


// SETUP
void setup() {
  Wire.begin();  // start i2c library; if not, RTC will not work
  RTC.begin();  // start RTC library
   // Serial.begin(9600);
       lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for");
  lcd.setCursor(0, 1);
  lcd.print("SD card");
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();
  
  fps.Open();
  fps.SetLED(true);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FPS Attendance");
  lcd.setCursor(0, 1);
  lcd.print(" System");
  delay(2000);
 // RTC.adjust(DateTime(__DATE__, __TIME__));  // set RTC time to compiling time
//  Serial.println("Setup Ready");
}

// MAIN PROGRAM
void loop() {
  succesRead = getID(); // read RFID tag
  if(succesRead<200){ // if RFID read was succesful
     // Serial.println("Roll Number :");
     // Serial.println(rollNum);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Roll Number");
      lcd.print(succesRead);
      lcd.setCursor(0, 1);
      lcd.print("Storing Data");
      delay(1000);
      StoreData(succesRead);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Please Reset");

    } 
    else { // beeb an error; if new tag, then exit
    //  Serial.println("Press the Finger");
      DateTime time = RTC.now();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(time.day(), DEC);
      lcd.print('/');
      lcd.print(time.month(), DEC);
      lcd.print('/');
      lcd.print(time.year(), DEC);
      lcd.print(' ');
  if (time.hour()<10)
  lcd.print('0');
  lcd.print(time.hour(), DEC);
  lcd.print(':');
  if (time.minute()<10)
  lcd.print('0');
  lcd.print(time.minute(), DEC);
  lcd.setCursor(0, 1);
  lcd.println("Press the Finger");
     }
     delay(100);
     succesRead=500;
  }  

int getID() {
 // Serial.println("Came to getID");
  if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
    int rollNum = fps.Identify1_N();
       if (rollNum<200)
       { //If a new PICC placed to RFID reader continue
       // Serial.println("Know Finger Found");
        return rollNum;
       }
       else
       {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Student not");
        lcd.setCursor(0,1);
        lcd.print("Found");
        delay(2000);
        }
  } 
  return 300;
}

void StoreData(int rollNum){ // calculate and store data to SD card
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Storing");
      DateTime time = RTC.now();
      int lDate,lMonth,lHour,lMinute;
      lDate=(time.day());
      lMonth=(time.month());
      lHour=(time.hour());
      lMinute=(time.minute());
  //Serial.println("Came to Storage");
  myFile.open("LOG.CSV", O_RDWR | O_CREAT | O_AT_END);
  myFile.println("*");
  myFile.print(rollNum, DEC);
  myFile.print(",");
  myFile.print(lDate);
  myFile.print("/");
  myFile.print(lMonth);
  myFile.print(",");
  myFile.print(lHour); 
  myFile.print(":");
  myFile.print(lMinute);
  myFile.print(",");
  myFile.println("*");
   myFile.close();
//  Serial.println("Saved");
delay(2000);
}

