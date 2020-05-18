#include                <Arduino.h>
#include                <avr/pgmspace.h>
#include                <SoftwareSerial.h>
#include                <TinyGPS++.h>
#include                "I2Cdev.h"
#include                "MPU6050.h"

// ----------------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------------


int16_t ax, ay, az;
int16_t gx, gy, gz;
const unsigned int      textScanTimeout = 15UL;             // secs between scans for inbound texts
int OkLED=13;
// ----------------------------------------------------------------------------
// global variables
// ----------------------------------------------------------------------------

TinyGPSPlus             gps;
char                    s[80];                              // generic buffer
SoftwareSerial          ssGprs(3, 4);
SoftwareSerial          ssGps(5, 6);
MPU6050 accelgyro;

// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------

void delOldSms();
void doGpsIo();
void gpsTest();
void powerUpSms();
int8_t sendAtCmd(
    char*               atCmd,
    char*               matchStr,
    unsigned int        timeout
    );
void sendCoord();

// ----------------------------------------------------------------------------
// delete all existing text messages from server


// ----------------------------------------------------------------------------
// process GPS's output

void doGpsIo(
    ) {

char                    c;

// accept each character from GPS, and send to the GPS decoder
while (ssGps.available() > 0) {
    c = ssGps.read();
//  Serial.print(c);                                        // uncomment for debugging
    gps.encode(c);
    }

} // doGpsIo

// ----------------------------------------------------------------------------
// if any waiting texts, send coordinates


// ----------------------------------------------------------------------------
// Displays current gps data

void gpsTest(
    )  {

if (!gps.location.isValid()) {
    Serial.println("no GPS location fix");
    return;
    }

if (gps.charsProcessed() < 10) {
  Serial.println(F("WARNING: No GPS data.  Check wiring."));
  return;
  }

Serial.print(F("https://www.google.com/maps/?q="));
if (gps.location.age() > 5000)
    Serial.print(F("xxx.xxxxxx,xxx.xxxxxx"));
else {
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.print(gps.location.lng(), 6);
    }
Serial.print(F("; "));

if (gps.speed.age() > 5000)
    Serial.print(F("xxx"));
else
    Serial.print(gps.speed.mph(), 0);
Serial.print(F(" MPH;"));

Serial.print(F("Course: "));
if (gps.course.age() > 5000)
    Serial.print(F("xxx"));
else
    Serial.print(gps.course.deg(), 0);
Serial.println(F(";"));


if (ssGps.overflow())
    Serial.println(F("ssGps buffer overflowed"));

} // gpsTest

// ----------------------------------------------------------------------------
// turn the GPRS unit on.
// At the moment I don't have it wired such that this will actually work.
// It will just wait until the GPRS is turned on.


// ----------------------------------------------------------------------------
// send AT command to GPRS

int8_t sendAtCmd(
    char*               atCmd,
    char*               matchStr,
    unsigned int        timeout
    ){

    char                c;
    uint8_t             x               = 0;
    uint8_t             answer          = 0;
    unsigned long       previous;

delay(100);

while (ssGprs.available() > 0)                          // flush buffer
    ssGprs.read();

ssGprs.println(atCmd);                              // Send the AT command

previous = millis();

// this loop waits for the answer
do {
    if (x == sizeof(s)-1) {
        Serial.println(F("**S buffer overflow**"));
        while (true) {}
        }

    // if there is data in the input buffer, read it and check for the asnwer
    if(ssGprs.available() != 0) {
        c = ssGprs.read();
        if (c == '\r' || c == '\n')                         // if a full line is read w/o finding text, clear buffer
            x = 0;
        s[x]   = c;
        s[x+1] = '\0';
//      Serial.print(s[x]);                                 // uncomment if you need to see modem responses

        // check if the desired answer is in the response of the module
        if (strstr(s, matchStr) != NULL) {
            answer = 1;
            }
        x    = x + 1;
        }
    // Waits for the answer with time out
    } while ((answer == 0) && ((millis() - previous) < timeout));

return answer;

} //sendAtCmd

// ----------------------------------------------------------------------------
// sendCoordinates via text message

void sendCoord(
    ) {

int8_t                  answer;


// wait for 1 or 5 which means register to home network or registered - roaming
// http://m2msupport.net/m2msupport/atcreg-network-registration/
while((sendAtCmd("AT+CREG?", "+CREG: 0,1", 500) ||
        sendAtCmd("AT+CREG?", "+CREG: 0,5", 500)) == 0) {}


sendAtCmd("AT+CMGF=1", "OK", 1000);                     // sets the SMS mode to text

answer = sendAtCmd("AT+CMGS=\"9404292958\"", ">", 2000);

if (answer == 1) {
    ssGprs.print(F("ACCIDENT DETECTED AT : "));
    ssGprs.print(gps.location.lat(), 6);
    ssGprs.print(F(","));
    ssGprs.print(gps.location.lng(), 6);
    ssGprs.print(F("; "));
    ssGprs.print(F("SEND HELP"));
    ssGprs.println(F(";"));
    ssGprs.write(0x1A);
    answer = sendAtCmd("", "OK", 20000);
    if (answer == 1)
        Serial.println(F("  SMS Sent"));
    else
        Serial.println(F("  SMS Send Error"));
    }

} // sendCoord

// ----------------------------------------------------------------------------
// setup

void setup(
    ) {
pinMode(OkLED,OUTPUT);
digitalWrite(OkLED,LOW);
Serial.begin(19200);   
Wire.begin();
    
    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

                                     // the Serial port of Arduino baud rate.

Serial.print(F("gsmGpsSmsDemo. "));
Serial.print(F(" Compiled: "));
Serial.print(F(__DATE__));
Serial.print(F(" "));
Serial.print(F(__TIME__));
Serial.print(F("."));
Serial.println();


ssGprs.begin(4800);                                         // the GPRS baud rate
ssGps.begin(9600);                                          // SMS baud rate

ssGprs.listen();                                            // listen to GPRS rx pin
ssGps.listen();                                             // listen to GPS rx pin

} // setup

// ----------------------------------------------------------------------------
// loop

void loop(
    ) {

char                c;
unsigned long       timeout             = 0UL;

Serial.println("Press 'T' to send coordinates via Text.");

while (true) {
            accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
            Serial.println(gx);
            if(az<=-32000)
            {
            Serial.println("Are You Okay?");
            for(int i=0;i<10;i++)
            {
             digitalWrite(OkLED,HIGH);
             delay(1000); 
             digitalWrite(OkLED,LOW);
             delay(1000); 
             }
            ssGprs.listen();                                // listen to GPRS while we send coordinates
            sendCoord();                                    // send coordinates as SMS msg
            ssGps.listen();                                 // go back to listening to GPS
            }
        

    doGpsIo();                                              // decode next GPS character

    if (millis() > timeout) {                               // ever <timeout> secs,  check for SMS
        ssGprs.listen();                                    // start listening to GPRS
        ssGps.listen();                                     // go back to listening to GPS
        timeout = millis() + textScanTimeout * 1000UL;      // determine next time to check for SMS
        }

    } // main while
  }
