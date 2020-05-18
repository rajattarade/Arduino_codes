
#include <SoftwareSerial.h>

#include <TinyGPS.h>

#include "Adafruit_FONA.h"


#define FONA_RX 4
#define FONA_TX 3
#define Trigger 9
#define FONA_RST 8

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

long int callerIDbuffer = "9404292958";




TinyGPS gps;
SoftwareSerial ss(5, 6);



static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_str(const char *str, int len);
String strL, strN, poss, tareq, textForSMS;
char charL[10], charN[10], text[400];
int o = 1;
boolean started = false;


void setup()


{
 Serial.begin(9600);
 ss.begin(9600);
}


void loop()
{
 float flat, flon;
 unsigned long age, date, time, chars = 0;
 unsigned short sentences = 0, failed = 0;


 while (o<4) {
   gps.f_get_position(&flat, &flon, &age);
   textForSMS = "tareq Home"; //testing gps from here
   Serial.println(textForSMS);
   Serial.print("longitude: ");
   print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
   Serial.println("");
   Serial.print("latitude : ");
   print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
   smartdelay(1000);
   Serial.println(""); //till here
   delay(1000);
   o++;
 }
   Serial.println("nil"); //to check whether 'if' works
 dtostrf(flat, 8, 6, charL);
 for (int i = 0; i < 10; i++)
 {
   strL += charL[i];
 }
 dtostrf(flon, 8, 6, charN);
 for (int i = 0; i < 10; i++)
 {
   strN += charN[i];
 }

 tareq = "tareq Home Location";
 tareq = tareq + "\nlongitude: " + strN + "\nlatitude :  " + strL;
 poss = tareq;
 poss.toCharArray(text, 400);

 delay(1000);
 
 Serial.print("..........................");
 Serial.println(text);
 


 //}
 //o++;
}
static void smartdelay(unsigned long ms)
{
 unsigned long start = millis();
 do
 {
   while (ss.available())
     gps.encode(ss.read());
 } while (millis() - start < ms);
}


static void print_float(float val, float invalid, int len, int prec)
{
 if (val == invalid)
 {
   while (len-- > 1)
     Serial.print('*');
   Serial.print(' ');
 }
 else
 {
   Serial.print(val, prec);
   int vi = abs( val);
   int flen = prec + (val < 0.0 ? 2 : 1); // . and -
   flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
   for (int i = flen; i < len; ++i)
     Serial.print(' ');
 }
 smartdelay(0);
}


static void print_str(const char *str, int len)
{
 int slen = strlen(str);
 for (int i = 0; i < len; ++i)
   Serial.print(i < slen ? str[i] : ' ');
 smartdelay(0);
}
