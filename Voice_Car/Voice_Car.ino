
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
String readvoice = "";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
    pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() { // run over and over
  if (mySerial.available()) {
    char c = mySerial.read();
    readvoice += c;
    
    if (readvoice == "1")
    {
      Serial.println("Forward");
      digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
      delay(500);                       // wait for a second
      digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
    }
    if (readvoice == "2")
    {
      digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500);                       // wait for a second
      digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
    }
    if (readvoice == "3")
    {
      digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
      delay(500);                       // wait for a second
      digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
    }
    if (readvoice == "4")
    {
      digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500);                       // wait for a second
      digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
    }
  }
  readvoice = "";

}

