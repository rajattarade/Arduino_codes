#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define pushButton2 2
#define pushButton3 3
#define pushButton4 4
#define pushButton5 5
#define pushButton6 6
#define pushButton7 7
#define pushButton8 8
#define pushButton9 9
#define pushButtonA0 A0
#define pushButtonA4 A4
#define pushButtonA5 A5


/*Create a unique pipe out. The receiver has to 
  wear the same unique code*/
  
const uint64_t pipeOut = 0xE8E8F0F0E1LL; //IMPORTANT: The same as in the receiver

RF24 radio(A1, 10); // select  CSN  pin

// The sizeof this struct should not exceed 32 bytes
// This gives us up to 32 8 bits channals
struct MyData {
  byte mov;
  byte gun;
  byte light1;
  byte light2;
  byte fire;
};

MyData data;

void resetData() 
{
  data.mov = 0;
  data.gun = 0;
  data.light1 = 0;
  data.light2 = 0;
  data.fire = 0;
}

void setup()
{
  //Start everything up
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  resetData();
}

void loop()
{
  // The calibration numbers used here should be measured 
  // for your joysticks till they send the correct values.
  resetData();
  if(digitalRead(pushButtonA5))
  data.light1=1;
  else
  data.light1=0;
  if(digitalRead(pushButtonA4))
  data.light2=1;
  else
  data.light2=0;
  
 if(digitalRead(pushButtonA0))
 {
  data.fire=1;
 }
  if(digitalRead(pushButton9))
 {
  data.gun=2;
 }
  if(digitalRead(pushButton7))
 {
  data.gun=1;
 }
  if(digitalRead(pushButton8))
 {
  data.gun=4;
 }
  if(digitalRead(pushButton6))
 {
  data.gun=3;
 }
  if(digitalRead(pushButton5))
 {
  data.mov=4;
 }
  if(digitalRead(pushButton3))
 {
  data.mov=3;
 }
  if(digitalRead(pushButton2))
 {
  data.mov=2;
 }
  if(digitalRead(pushButton4))
 {
  data.mov=1;
 }

  radio.write(&data, sizeof(MyData));
}
