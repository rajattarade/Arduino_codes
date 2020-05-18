const int stepPinX = 2; 
const int dirPinX = 5; 
const int stepPinY = 3; 
const int dirPinY = 6; 
const int nxtButton = 11; 

const int stepperenb = 8;
const int spindle = A3;
 

 
void setup() {
  // Sets the two pins as Outputs
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
  digitalWrite(stepperenb,HIGH); // Enables the motor
  Serial.println("READY");
  while(digitalRead(nxtButton));
  delay(100);
  while(digitalRead(nxtButton));
  Serial.println("Running");
  digitalWrite(dirPinX,HIGH); // Towards Motor
  digitalWrite(stepperenb,LOW); // Enables the motor
  
  for(int x = 0; x < 2000; x++) {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
  digitalWrite(spindle,LOW);
  
  digitalWrite(dirPinY,HIGH); // Towards Motor
  for(int x = 0; x < 1000; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
  digitalWrite(spindle,HIGH); 
  digitalWrite(stepperenb,HIGH); // Enables the motor to move in a particular direction
  Serial.println("Ready");
  
  while(digitalRead(nxtButton));
  delay(100);
  while(digitalRead(nxtButton));

  Serial.println("NEXT");

  digitalWrite(spindle,LOW);
  digitalWrite(dirPinX,LOW); // Away Motor
  digitalWrite(stepperenb,LOW); // Enables the motor
  
  for(int x = 0; x < 1500; x++) {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
  /////////////////////////////////////AT 1500///////////////////////////////////////////////////////
 digitalWrite(dirPinX,LOW); // Away Motor
 for(int x = 0; x < 500; x++)
 {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(2500); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(2500); 
  }
  delay(1000);
 digitalWrite(dirPinX,HIGH); // Towards Motor
 for(int x = 0; x < 500; x++)
  {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
 /////////////////////////////////////FIRST CUT DONE///////////////////////////////////////////////////////
 
  digitalWrite(dirPinY,LOW); // Away Motor
  for(int x = 0; x < 250; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
   digitalWrite(dirPinX,LOW); // Away Motor
 for(int x = 0; x < 500; x++)
 {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(2500); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(2500); 
  }
  delay(1000);
 digitalWrite(dirPinX,HIGH); // Towards Motor
 for(int x = 0; x < 500; x++)
  {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
 ///////////////////////////////////// CUT DONE `750///////////////////////////////////////////////////////
  digitalWrite(dirPinY,LOW); // Away Motor
  for(int x = 0; x < 250; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
   digitalWrite(dirPinX,LOW); // Away Motor
 for(int x = 0; x < 500; x++)
 {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(2500); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(2500); 
  }
  delay(1000);
 digitalWrite(dirPinX,HIGH); // Towards Motor
 for(int x = 0; x < 500; x++)
  {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
 ///////////////////////////////////// CUT DONE `500///////////////////////////////////////////////////////
   digitalWrite(dirPinY,LOW); // Away Motor
  for(int x = 0; x < 250; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
   digitalWrite(dirPinX,LOW); // Away Motor
 for(int x = 0; x < 500; x++)
 {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(2500); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(2500); 
  }
  delay(1000);
 digitalWrite(dirPinX,HIGH); // Towards Motor
 for(int x = 0; x < 500; x++)
  {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(1000); 
  }
 ///////////////////////////////////// CUT DONE `250///////////////////////////////////////////////////////   
   digitalWrite(dirPinY,LOW); // Away Motor
  for(int x = 0; x < 550; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  }
  delay(500);
     digitalWrite(dirPinY,HIGH); // Away Motor
  for(int x = 0; x < 300; x++) {
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(1000); 
  } 
     digitalWrite(dirPinX,LOW); // Away Motor
 for(int x = 0; x < 500; x++)
 {
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(2500); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(2500); 
  }
 ///////////////////////////////////// CUT DONE `0/////////////////////////////////////////////////////// 
   digitalWrite(spindle,HIGH);
  while(digitalRead(nxtButton));
  delay(100);
  while(digitalRead(nxtButton));  
  
  while(1);
}
