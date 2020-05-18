#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include "Adafruit_FONA.h"

#define FONA_RX 4
#define FONA_TX 3
#define Trigger 9
#define FONA_RST 8

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

TinyGPS gps;
SoftwareSerial ss(5, 6);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

long int callerIDbuffer = "9404292958";
float flat, flon;

void setup()
{
  pinMode(Trigger, INPUT);
  Serial.begin(115200);
  ss.begin(9600);

  // put your setup code here, to run once:void setup() 
  while (!Serial);

  Serial.println(F("FONA SMS caller ID test"));
  Serial.println(F("Initializing....(May take 3 seconds)"));

  // make it slow so its easy to read!
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while(1);
  }
  Serial.println(F("FONA is OK"));

  
  Serial.println("FONA Ready");
 // fona.sendSMS(callerIDbuffer, "Setup Ready");

  Serial.print("Simple TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart");
  Serial.println();
}

void loop()
{

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
 for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (1)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat,6);
    Serial.print(" LON=");
    Serial.println(flon, 6);
   }
  /*if(Trigger==0)
  {
   Serial.print("SMS Sent");
   fona.sendSMS(callerIDbuffer, 'flat'); 
  }*/  
}
