#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



const uint64_t pipeIn =  0xE8E8F0F0E1LL;

RF24 radio(8, 10); // CE, CSN

// The sizeof this struct should not exceed 32 bytes
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
  data.mov = 9;
  data.gun = 9;
  data.light1 = 9;
  data.light2 = 9;
  data.fire = 9;
}

void setup()
{   
  Serial.begin(19200);
  resetData();
  radio.begin();
  radio.setDataRate(RF24_250KBPS); // Both endpoints must have this set the same
  radio.setAutoAck(false);
   
  Serial.println("READY");

  delay(500);
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();

}

/**************************************************/

unsigned long lastRecvTime = 0;

void recvData()
{  
  while ( radio.available() ) {        
    radio.read(&data, sizeof(MyData));
    lastRecvTime = millis();
  }
}

/**************************************************/

void loop()
{
  recvData();
  Serial.print(data.mov);
  Serial.print("\t");
  Serial.print(data.gun);
  Serial.print("\t");
  Serial.print(data.light1);
  Serial.print("\t");
  Serial.print(data.light2);
  Serial.print("\t");
   Serial.print(data.fire);
  Serial.print("\t");
  Serial.println();
  
  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    // signal lost?
    resetData();
  }
  
}



