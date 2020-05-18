#include <Servo.h>

Servo updown;
Servo leftright;
int ud=70;
int lr=0;

int topleft;
int topright;
int downleft;
int downright;
String pos; 
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  updown.attach(9);
  leftright.attach(10);
}

void loop() {

  topleft = analogRead(A3);//a3
  topright = analogRead(A2);//a2
  downleft = analogRead(A0);//a0
  downright = analogRead(A1);//a1
            // tell servo to go to position in variable 'pos'
 leftright.write(lr);
 updown.write(ud);

 
  if(topleft>20)
  Serial.print(1);
  else
  {
    if(downleft<20)
    {
     lr=lr+1;
     if(lr>180)
     lr=180;
    }
    Serial.print(0);
  } 
  Serial.print("\t");
  
  if(topright>20)
  Serial.print(1);
  else
  {
    if(topleft<20)
    {
     ud=ud+1;
     if(ud>70)
     ud=70;
    }
    if(downright<20)
    {
     lr=lr-1;
     if(lr<0)
     lr=0;
    }
    Serial.print(0);
  }  
  Serial.print("\t");
  
  if(downleft>20)
  Serial.print(1);
  else
  Serial.print(0); 
  Serial.print("\t");
  
  if(downright>20)
  Serial.print(1);
  else
  {
    if(downleft<20)
    {
     ud=ud-1;
     updown.write(ud);
    }
    Serial.print(0);
  } 
  Serial.print("\t");
  Serial.print(lr);
  Serial.print("\t");
  Serial.print(ud);
  
 
  Serial.println();


  
  
 delay(20);
}
