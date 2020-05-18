#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

RF24 radio(9,10);

void setup()
{
 while (!Serial);
 Serial.begin(9600);
 printf_begin();
 radio.begin();
 radio.setDataRate(RF24_250KBPS);
 radio.setPALevel(RF24_PA_LOW);
}

void loop()
{
 radio.printDetails();
 delay(5000);
 
  radio.setPALevel(RF24_PA_HIGH);
  radio.printDetails();
  while(1);
}
