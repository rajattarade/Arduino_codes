#include <EEPROM.h>

//Declaration of connections
const int stepPinX = 2; 
const int dirPinX = 5; 
const int stepPinY = 3; 
const int dirPinY = 6; 
const int nxtButton = 11; 
const int stepperenb = 8;
const int spindle = A3;

int value;

 
void setup() {
  // Sets the pins as Outputs
  pinMode(stepPinX,OUTPUT); 
  pinMode(dirPinX,OUTPUT);
  pinMode(stepPinY,OUTPUT); 
  pinMode(dirPinY,OUTPUT);
  pinMode(stepperenb, OUTPUT);
  pinMode(spindle, OUTPUT);
  digitalWrite(spindle,HIGH); 
  pinMode(nxtButton, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Init");
}
void loop() {
  value = EEPROM.read(0);
 
  if(value>=2)
  {
  printf("BLOCK FOREVER");
  delay(100);
  while(1);
  }
/* while(1)
  {
    digitalWrite(spindle,HIGH);
    while(digitalRead(nxtButton));
    delay(100);
    while(digitalRead(nxtButton));
    digitalWrite(spindle,LOW);

      digitalWrite(dirPinY,LOW); // Away Motor
  for(int y = 0; y < 300; y++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(2000); 
  }
  digitalWrite(dirPinY,HIGH); // Away Motor
  for(int x = 0; x < 100; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
  digitalWrite(spindle,HIGH);
      while(digitalRead(nxtButton));
    delay(100);
    while(digitalRead(nxtButton));
  }*/
  digitalWrite(stepperenb,HIGH); // Stepper motors disabled
  Serial.println("READY");
  while(digitalRead(nxtButton)); //
  delay(100);                    //block till button is pressed
  while(digitalRead(nxtButton)); //
  Serial.println("Running");
  
  digitalWrite(dirPinX,HIGH); // Direction Towards Motor
  digitalWrite(stepperenb,LOW); // Stepper motors enabled
  
  for(int x = 0; x < 1000; x++) { //1000 steps travel
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
  digitalWrite(spindle,LOW); // Spindle enable
  
  digitalWrite(dirPinY,HIGH); 
  for(int x = 0; x < 900; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(2000); 
  }
  digitalWrite(spindle,HIGH); 
  digitalWrite(stepperenb,HIGH); 
  Serial.println("Ready");
  
  while(digitalRead(nxtButton));
  delay(100);
  while(digitalRead(nxtButton));

  Serial.println("NEXT");

  digitalWrite(spindle,LOW);
  digitalWrite(dirPinX,LOW); // Away Motor
  digitalWrite(stepperenb,LOW); // Enables the motor
  
  for(int x = 0; x < 900; x++) {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
  /////////////////////////////////////AT 1500///////////////////////////////////////////////////////
  digitalWrite(dirPinX,LOW); // Away Motor
 for(int z = 0; z < 13; z++)
 {
 for(int x = 0; x < 10; x++)
 {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
 }
 delay(3000);
 }
 digitalWrite(dirPinX,HIGH); // Towards Motor
 for(int x = 0; x < 100; x++)
  {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
  /////////////////////////////////////FIRST CUT DONE///////////////////////////////////////////////////////  
  digitalWrite(dirPinY,LOW); // Away Motor
  for(int y = 0; y < 300; y++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(2000); 
  }
  digitalWrite(dirPinY,HIGH); // Away Motor
  for(int x = 0; x < 100; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
  delay(1000);

 digitalWrite(dirPinX,LOW); // Away Motor
 for(int z = 0; z < 13; z++)
 {
 for(int x = 0; x < 10; x++)
 {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
 }
 delay(3000);
 }
 digitalWrite(dirPinX,HIGH); // Towards Motor
 for(int x = 0; x < 120; x++)
  {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
  ///////////////////////////////////// CUT DONE Y `800///////////////////////////////////////////////////////
      digitalWrite(dirPinY,LOW); // Away Motor
  for(int y = 0; y < 300; y++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(2000); 
  }
  digitalWrite(dirPinY,HIGH); // Away Motor
  for(int x = 0; x < 100; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
  delay(1000);

 digitalWrite(dirPinX,LOW); // Away Motor
 for(int z = 0; z < 13; z++)
 {
 for(int x = 0; x < 10; x++)
 {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
 }
 delay(3000);
 }
 digitalWrite(dirPinX,HIGH); // Towards Motor
 for(int x = 0; x < 120; x++)
  {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
   ///////////////////////////////////// CUT DONE `600///////////////////////////////////////////////////////
      digitalWrite(dirPinY,LOW); // Away Motor
  for(int y = 0; y < 300; y++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(2000); 
  }
  digitalWrite(dirPinY,HIGH); // Away Motor
  for(int x = 0; x < 100; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
  delay(1000);
 digitalWrite(dirPinX,LOW); // Away Motor
 for(int z = 0; z < 13; z++)
 {
 for(int x = 0; x < 10; x++)
 {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
 }
 delay(3000);
 }
 digitalWrite(dirPinX,HIGH); // Towards Motor
 for(int x = 0; x < 120; x++)
  {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
   ///////////////////////////////////// CUT DONE `400///////////////////////////////////////////////////////
      digitalWrite(dirPinY,LOW); // Away Motor
  for(int y = 0; y < 300; y++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(2000); 
  }
  digitalWrite(dirPinY,HIGH); // Away Motor
  for(int x = 0; x < 100; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
  delay(1000);
  
 digitalWrite(dirPinX,LOW); // Away Motor
 for(int z = 0; z < 13; z++)
 {
 for(int x = 0; x < 10; x++)
 {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
 }
 delay(3000);
 }
 digitalWrite(dirPinX,HIGH); // Towards Motor
 for(int x = 0; x < 500; x++)
  {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
   ///////////////////////////////////// CUT DONE `200///////////////////////////////////////////////////////
      digitalWrite(dirPinY,LOW); // Away Motor
  for(int x = 0; x < 550; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
  delay(500);
     digitalWrite(dirPinY,HIGH); // Away Motor
  for(int x = 0; x < 350; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  } 
   digitalWrite(dirPinX,LOW); // Towards Motor
 for(int x = 0; x < 500; x++)
  {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  } 
   digitalWrite(spindle,HIGH); 
     
  value = EEPROM.read(0);
  value = value+1;
  EEPROM.write(0, value);
  while(1);
}
