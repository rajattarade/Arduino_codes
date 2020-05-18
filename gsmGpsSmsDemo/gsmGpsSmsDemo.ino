#include                <Arduino.h>
#include                <avr/pgmspace.h>
#include                <SoftwareSerial.h>
#include                <TinyGPS++.h>

// ----------------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------------

const bool              debugDefault    = false;            // default debugmode
const unsigned int      textScanTimeout = 15UL;             // secs between scans for inbound texts
const int               onModulePin     = 9;
// ----------------------------------------------------------------------------
// global variables
// ----------------------------------------------------------------------------

bool                    debugMode       = debugDefault;
TinyGPSPlus             gps;
char                    s[80];                              // generic buffer
SoftwareSerial          ssGprs(3, 4);
SoftwareSerial          ssGps(5, 6);

// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------

void delOldSms();
void doGpsIo();
void doSmsMsg();
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

void delOldSms(
    ) {

if (debugMode)
    Serial.println("@delOldSms");

if (sendAtCmd("at+cmgda=\"DEL ALL\"","OK",5000) == 0)
    if (debugMode)
        Serial.println("  delete failed.");

} // delOldSms

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

void doSmsMsg(
    ) {

if (debugMode)
    Serial.println("@doSmsMsg");

if (sendAtCmd("at+cmgl=\"ALL\"", "+CMGL:", 5000) == 1) {
    // new text found, respond (we don't actually parse the text in any way)
    if (debugMode)
        Serial.println("  new SMS msg found");
    sendCoord();
    delOldSms();
    }
else {
    if (debugMode)
        Serial.println("  no new SMS msg found");
    }

} // doSmsMsg


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

if (debugMode) {
    Serial.print(F("  Sentences that failed checksum="));
    Serial.println(gps.failedChecksum());
    }

if (ssGps.overflow())
    Serial.println(F("ssGps buffer overflowed"));

} // gpsTest

// ----------------------------------------------------------------------------
// turn the GPRS unit on.
// At the moment I don't have it wired such that this will actually work.
// It will just wait until the GPRS is turned on.

void powerUpSms(){
uint8_t                 answer          = 0;
   
    Serial.println(F("@powerUpSms"));
// checks if the module is started
answer = sendAtCmd("AT", "OK", 2000);
while (answer == 0) {
        Serial.println(F("  no answer, pulsing power pin."));
    // power on pulse
    digitalWrite(onModulePin,LOW);
        Serial.println(F("pin Low"));
    delay(3000);
    digitalWrite(onModulePin,HIGH);
        Serial.println(F("pin High"));
        delay(15000);
        answer = sendAtCmd("AT", "OK", 2000);
    }

} // powerUpSms

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

if (debugMode)
    Serial.println(F("@sendCoor"));

if (debugMode)
    Serial.println(F("  Connecting to the network..."));

// wait for 1 or 5 which means register to home network or registered - roaming
// http://m2msupport.net/m2msupport/atcreg-network-registration/
while((sendAtCmd("AT+CREG?", "+CREG: 0,1", 500) ||
        sendAtCmd("AT+CREG?", "+CREG: 0,5", 500)) == 0) {}

if (debugMode)
    Serial.println(F("  Setting SMS mode..."));

sendAtCmd("AT+CMGF=1", "OK", 1000);                     // sets the SMS mode to text

if (debugMode)
    Serial.println(F("  Sending SMS..."));

answer = sendAtCmd("AT+CMGS=\"9404292958\"", ">", 2000);

if (answer == 1) {
    ssGprs.print(F("https://www.google.com/maps/?q="));
    ssGprs.print(gps.location.lat(), 6);
    ssGprs.print(F(","));
    ssGprs.print(gps.location.lng(), 6);
    ssGprs.print(F("; "));
    ssGprs.print(gps.speed.mph(), 0);
    ssGprs.print(F(" MPH;"));
    ssGprs.print(F("Course: "));
    ssGprs.print(gps.course.deg(), 0);
    ssGprs.println(F(";"));
    ssGprs.write(0x1A);
    answer = sendAtCmd("", "OK", 20000);
    if (answer == 1)
        Serial.println(F("  SMS Sent"));
    else
        Serial.println(F("  SMS Send Error"));
    }

if (debugMode)
    Serial.println(F("  returning to listening to GPS"));

} // sendCoord

// ----------------------------------------------------------------------------
// setup

void setup(
    ) {

unsigned long           debugTimer;

Serial.begin(19200);                                        // the Serial port of Arduino baud rate.
pinMode(onModulePin, OUTPUT);
Serial.print(F("gsmGpsSmsDemo. "));
Serial.print(F(" Compiled: "));
Serial.print(F(__DATE__));
Serial.print(F(" "));
Serial.print(F(__TIME__));
Serial.print(F("."));
Serial.println();

debugTimer = millis() + 4LU * 1000LU;
Serial.println(F("Press <CR> to enable debugging; otherwise wait 4 secs."));
while (millis() < debugTimer) {
    if (Serial.available()) {
        debugMode = true;
        Serial.println(F("debugging enabled"));
        break;
        }
    } // while

ssGprs.begin(4800);                                         // the GPRS baud rate
ssGps.begin(9600);                                          // SMS baud rate

ssGprs.listen();                                            // listen to GPRS rx pin
powerUpSms();                                               // wait for GPRS to power on
delOldSms();                                                // delete any waiting SMS msgs
ssGps.listen();                                             // listen to GPS rx pin
powerUpSms();
} // setup

// ----------------------------------------------------------------------------
// loop

void loop()
{
char                c;
unsigned long       timeout             = 0UL;

Serial.println("Press 'T' to send coordinates via Text.");

while (true) 
   {
    if (Serial.available()) {                               // did user hit 'T' key to force text?
        c = Serial.read();
        while (Serial.available())                          // flush buffer
            Serial.read();
        if (c == 'T' || c == 't') {
            ssGprs.listen();                                // listen to GPRS while we send coordinates
            sendCoord();                                    // send coordinates as SMS msg
            ssGps.listen();                                 // go back to listening to GPS
            }
        }

    doGpsIo();                                              // decode next GPS character

    if (millis() > timeout) {                               // ever <timeout> secs,  check for SMS
        if (debugMode)
            gpsTest();
        ssGprs.listen();                                    // start listening to GPRS
        doSmsMsg();                                         // check for incoming SMS and respond w/ coordinates
        ssGps.listen();                                     // go back to listening to GPS
        timeout = millis() + textScanTimeout * 1000UL;      // determine next time to check for SMS
        }

    } // main while
}
