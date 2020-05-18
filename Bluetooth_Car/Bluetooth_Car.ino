#include <SoftwareSerial.h>
SoftwareSerial BTSerial (11, 10);
// BTSerial (Rx, Tx); Based on the Aduno board
// Connect the pin of 11 pin of Arduino board to TX pin of Bluetooth module, connect Pin 12 and RX
#define EN1 2 // Motor A to motor driver A-1A pin connection
#define EN2 3 // Motor A to Motor Driver A-1B Pin Connection
#define EN3 4 // motor B and motor driver B-1A pin connection
#define EN4 5 // motor B and motor driver b-1B pin connection
#define SDR1 8 // motor B and motor driver b-1B pin connection
#define SDR2 9 // motor B and motor driver b-1B pin connection

int carSpeed = 200; // Speed of RC car

void setup () {
BTSerial.begin (9600); // Communication with Bluetooth module via software serial communication
Serial.begin(9600);
// Initialize both pins of motor A to output mode
pinMode (EN1, OUTPUT);
pinMode (EN2, OUTPUT);
// Initialize both pins of motor B to output mode
pinMode (EN3, OUTPUT);
pinMode (EN4, OUTPUT);
}
void loop () {
if (BTSerial.available ()) {
 char str = BTSerial.read(); // Save command received in Bluetooth to command
  Serial.println(str);
  if (str == 'F') {
    // function call to advance RC car when receiving F or f as input
    moving_forward ();
  }
  else if (str == 'B') {
    // function call to reverse RC car when receiving B or b as input
    moving_backward ();
  }
  else if (str == 'L') {
    // function call that rotates RC car left when receiving L or l as input
    moving_left ();
  }
  else if (str == 'R') {
    // function call that rotates RC car right when receiving R or r as input
    moving_right ();
  }
  else if (str == 'S') {
    // Function call to stop RC car when receiving S or s as input
    stop_moving ();
  }
  else if (str == 'A') {
    // Function call to stop RC car when receiving S or s as input
    forward_seeder ();
  }
  else if (str == 'C') {
    // Function call to stop RC car when receiving S or s as input
    reverse_seeder ();
  }
  else if (str == 'Y') {
    // Function call to stop RC car when receiving S or s as input
    stop_seeder ();
  }
  delay (100);
 // else
 // {stop_moving ();}
}
// Time delay
// delay (100);
}
void moving_forward () {
// Rotate motor A forward
digitalWrite (EN1, LOW);
digitalWrite (EN2, HIGH);
// Rotate motor B forward
digitalWrite (EN3, LOW);
digitalWrite (EN4, HIGH);
}
void moving_backward () {
// Rotate motor A in the reverse direction
digitalWrite (EN1, HIGH);
digitalWrite (EN2, LOW);
// Rotate motor B in the reverse direction
digitalWrite (EN3, HIGH);
digitalWrite (EN4, LOW);
}
void moving_left () {
// Rotate motor A in the reverse direction
digitalWrite (EN1, HIGH);
digitalWrite (EN2, LOW);
// Rotate motor B forward
digitalWrite (EN3, LOW);
digitalWrite (EN4, HIGH);
}
void moving_right () {
  // Rotate motor A forward
digitalWrite (EN1, LOW);
digitalWrite (EN2, HIGH);
// Rotate motor B in the reverse direction
digitalWrite (EN3, HIGH);
digitalWrite (EN4, LOW);
}
void stop_moving () {
digitalWrite (EN1, LOW);
digitalWrite (EN2, LOW);
digitalWrite (EN3, LOW);
digitalWrite (EN4, LOW);
}

void forward_seeder () {
digitalWrite (SDR1, HIGH);
digitalWrite (SDR2, LOW);
}
void reverse_seeder () {
digitalWrite (SDR1, LOW);
digitalWrite (SDR2, HIGH);
}
void stop_seeder () {
digitalWrite (SDR1, LOW);
digitalWrite (SDR2, LOW);
}
