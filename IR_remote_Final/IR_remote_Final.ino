#include "DigiKeyboard.h"

int irPin = 0; //Sensor pin connect to digital pin2 (ATINY85 pin7)
int start_bit = 2200; //Start bit threshold (Microseconds)
int bin_1 = 1000; //Binary 1 threshold (Microseconds)
int bin_0 = 400; //Binary 0 threshold (Microseconds)
const byte BIT_PER_BLOCK = 32;

void setup() {

  pinMode(0, INPUT);

  // don't need to set anything up to use DigiKeyboard
  DigiKeyboard.delay(1000);
}

void loop() {
   if(getIRKey()==1)
    {
      DigiKeyboard.print(" ");
    } 
}

/////////////////////////////////////////////////////////////
// decode infrared signal
// Code from http://www.instructables.com/id/DIY-USB-IR-receiver/
// TODO: Replace with IRLib
/////////////////////////////////////////////////////////////
int getIRKey() {
  int data[BIT_PER_BLOCK];
  int space[32]={0,1,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,1};
  int i;

  while (pulseIn(irPin, HIGH) < start_bit); // Wait for a start bit
  for (i = 0 ; i < BIT_PER_BLOCK ; i++)
    data[i] = pulseIn(irPin, HIGH); // Start measuring bits, I only want HIGH pulses

  delay(100);
  for (i = 0 ; i < BIT_PER_BLOCK ; i++) // Parse them
  {
    if (data[i] > bin_1) //is it#-1 a 1?
      data[i] = 1;
    else if (data[i] > bin_0) //is it a 0?
      data[i] = 0;
    else
      return -1; // Flag the data as invalid; Return -1 on invalid data
  }

  // Based on NEC protocol, command data started from bit 16
  // and end with bit 24 (8 bits long)
  int result = 0;
  for (i = 0 ; i < 32; i++) {
   if(data[i]!=space[i])// print out the value of button in binary form
   break;
  }
  if(i<30)
  return 0; // Return key number  else
  else
  return 1; // Return key number  else
}
//01000000101111110011100011000111

