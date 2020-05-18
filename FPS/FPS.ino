#include <SoftwareSerial.h>
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// need a serial port to communicate with the GT-511C3
SoftwareSerial btSerial(8, 7); // Arduino RX (GT TX), Arduino TX (GT RX)
// the Arduino TX pin needs a voltage divider, see wiring diagram at:
// http://startingelectronics.com/articles/GT-511C3-fingerprint-scanner-hardware/

void setup() {
  Serial.begin(9600);    // serial connection to processing app.
   lcd.begin(16, 2);
  btSerial.begin(9600);  // for communicating with the GT-511C3
}

byte rx_byte = 0;        // stores received byte

void loop() {
  // check for a byte from the GT-511C3
  if (btSerial.available()) {
    // get a byte from the FPS and send it to the processing app.
    rx_byte = btSerial.read();
    lcd.write(rx_byte);
  }
}
