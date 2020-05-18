#define r1 2
#define r2 3
#define r3 4
#define r4 5
#define outputA 6
#define outputB 7

 int counter = 0; 
 int Mcounter = 0;
 int aState;
 int aLastState;  

void setup() 
{
  // put your setup code here, to run once:
   pinMode (r1,OUTPUT);
   pinMode (r2,OUTPUT);
   pinMode (r3,OUTPUT);
   pinMode (r4,OUTPUT);
  digitalWrite(r1, HIGH);
  digitalWrite(r3, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r4, HIGH);
  delay(1000);
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   Serial.begin (9600);
   // Reads the initial state of the outputA
}

void loop() {
  // put your main code here, to run repeatedly:
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occurred
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) == aState)
     {
       counter ++;
     }
     else
     {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   if((Mcounter-counter)==3)
   {
    turnRight();
    Mcounter=counter;
   }
   if((Mcounter-counter)==-3)
   {
    turnLeft();
    Mcounter=counter;
   }
 }

void turnLeft()
{
digitalWrite(r1, LOW);
digitalWrite(r3, HIGH);
digitalWrite(r2, LOW);
digitalWrite(r4, HIGH);
delay(500);
digitalWrite(r1, HIGH);
digitalWrite(r3, HIGH);
digitalWrite(r2, HIGH);
digitalWrite(r4, HIGH);
}

void turnRight()
{
 digitalWrite(r1, HIGH);
digitalWrite(r3, LOW);
digitalWrite(r2, HIGH);
digitalWrite(r4, LOW);
delay(500);
digitalWrite(r1, HIGH);
digitalWrite(r3, HIGH);
digitalWrite(r2, HIGH);
digitalWrite(r4, HIGH);
}

