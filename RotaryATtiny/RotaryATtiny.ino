#include "DigiKeyboard.h"
const int EncoderA = 1;
const int EncoderB = 2;

// Rotary encoder **********************************************

volatile int a0;
volatile int c0;
volatile int Count = 0;

// Called when encoder value changes
void ChangeValue (bool Up) {
   Count = max(min((Count + (Up ? 1 : -1)), 1000), 0);
   DigiKeyboard.println(Count);
}

// Pin change interrupt service routine
ISR (PCINT0_vect) {
  int a = PINB>>EncoderA & 1;
  int b = PINB>>EncoderB & 1;
  if (a != a0) {              // A changed
    a0 = a;
    if (b != c0) {
      c0 = b;
      ChangeValue(a == b);
    }
  }
}

// Setup demo **********************************************

void setup() {
  pinMode(EncoderA, INPUT_PULLUP);
  pinMode(EncoderB, INPUT_PULLUP);
  PCMSK = 1<<EncoderA;        // Configure pin change interrupt on A
  GIMSK = 1<<PCIE;            // Enable interrupt
  GIFR = 1<<PCIF;             // Clear interrupt flag
}

void loop() {

}
