#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define L1_MOTOR 7
#define L2_MOTOR 6

#define R1_MOTOR 4
#define R2_MOTOR 5

#define UD1_MOTOR A0
#define UD2_MOTOR A1

#define LR1_MOTOR A3
#define LR2_MOTOR A2

#define LED A4
#define IRLED A5


const uint64_t pipeIn =  0xE8E8F0F0E1LL;
Servo myservo;
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
  pinMode(L1_MOTOR, OUTPUT);
  pinMode(L2_MOTOR, OUTPUT);
  pinMode(R1_MOTOR, OUTPUT);
  pinMode(R2_MOTOR, OUTPUT);
  pinMode(LR1_MOTOR, OUTPUT);
  pinMode(LR2_MOTOR, OUTPUT);
  pinMode(UD1_MOTOR, OUTPUT);
  pinMode(UD2_MOTOR, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(IRLED, OUTPUT);
  
  Serial.println("READY");
  myservo.attach(3);
  myservo.write(180); 
  delay(2000); 
  
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
  if(data.mov==0 || data.mov==9)
  halt();
  if(data.mov==1)
  forward();
  if(data.mov==2)
  reverse();
  if(data.mov==3)
  turnLeft();
  if(data.mov==4)
  turnRight();
  Serial.print(data.mov);
  Serial.print("\t");
  
  if(data.gun==0 || data.gun==9)
  halt();
  if(data.gun==1)
  gunUp();
  if(data.gun==2)
  gunDown();
  if(data.gun==3)
  gunLeft();
  if(data.gun==4)
  gunRight();
  Serial.print(data.gun);
  Serial.print("\t");

  if(data.light1==1)
  digitalWrite(LED, HIGH);
  else
  digitalWrite(LED, LOW);
  Serial.print(data.light1);
  Serial.print("\t");

  if(data.light2==1)
  digitalWrite(IRLED, HIGH);
  else
  digitalWrite(IRLED, LOW);
  Serial.print(data.light2);
  Serial.print("\t");
  
  if(data.fire==1)
  fire();
  Serial.print(data.fire);
  Serial.print("\t");
  Serial.println();
  delay(20);
  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    // signal lost?
    resetData();
  }
  
}

void halt()
{
   digitalWrite(L1_MOTOR, LOW);
   digitalWrite(L2_MOTOR, LOW);
   digitalWrite(R1_MOTOR, LOW);
   digitalWrite(R2_MOTOR, LOW);
   digitalWrite(LR1_MOTOR, LOW);
   digitalWrite(LR2_MOTOR, LOW);
   digitalWrite(UD1_MOTOR, LOW);
   digitalWrite(UD2_MOTOR, LOW);
   myservo.write(180);
}

void forward()
{
   digitalWrite(L1_MOTOR, HIGH);
   digitalWrite(L2_MOTOR, LOW);
   digitalWrite(R1_MOTOR, HIGH);
   digitalWrite(R2_MOTOR, LOW);
   delay(100);
}

void reverse()
{
   digitalWrite(L1_MOTOR, LOW);
   digitalWrite(L2_MOTOR, HIGH);
   digitalWrite(R1_MOTOR, LOW);
   digitalWrite(R2_MOTOR, HIGH);
   delay(100);
}

void turnRight()
{
   digitalWrite(L1_MOTOR, LOW);
   digitalWrite(L2_MOTOR, HIGH);
   digitalWrite(R1_MOTOR, HIGH);
   digitalWrite(R2_MOTOR, LOW);
   delay(100);
}

void turnLeft()
{
   digitalWrite(L1_MOTOR, HIGH);
   digitalWrite(L2_MOTOR, LOW);
   digitalWrite(R1_MOTOR, LOW);
   digitalWrite(R2_MOTOR, HIGH);
   delay(100);
}

void gunLeft()
{
   digitalWrite(3, LOW);
   digitalWrite(LR1_MOTOR, LOW);
   digitalWrite(LR2_MOTOR, HIGH);
}

void gunRight()
{
   digitalWrite(LR1_MOTOR, HIGH);
   digitalWrite(LR2_MOTOR, LOW);
}

void gunUp()
{
   digitalWrite(UD1_MOTOR, HIGH);
   digitalWrite(UD2_MOTOR, LOW);
}

void gunDown()
{
   digitalWrite(UD1_MOTOR, LOW);
   digitalWrite(UD2_MOTOR, HIGH);
}

void fire()
{  Serial.println("FIRE");
   myservo.write(150);
   delay(500);
}


