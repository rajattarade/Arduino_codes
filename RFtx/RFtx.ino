#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
char ptext[] = "T";
const byte address[6] = "00001";
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(A7, INPUT);
}
void loop() {
  char text[] = "T";
  if(analogRead(A7)<500)
  text[1] = '1';
  else
  text[1] = '0';
  if(ptext != text)
  {
  radio.write(&text, sizeof(text));
   for(int l = 0; l < sizeof(text); l++)
   {
      ptext[l] = text[l];
   }
  }
  delay(100);
}
