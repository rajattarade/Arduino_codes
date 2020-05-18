#include <LiquidCrystal.h> //Include the library that enables you to use the LCD

/*------ Arduino Line Follower Code----- */
/*-------definning Inputs------*/
#define LS 4      // left sensor
#define RS 3      // right sensor
const byte WS = 2;

 int tempL = 0;
 int tempR = 0;
 #define room1 9
 #define room2 10
 #define room3 11
 int r1=0,r2=0,r3=0;
 int room = 0;
LiquidCrystal lcd(A0,A1,A2,A3, A4, A5);//Declare that your LCD is connected to pins 2,3,4,5,6 & 7 on your Arduino

 
/*-------definning Outputs------*/
#define LM1 5       // left motor
#define LM2 6       // left motor
#define RM1 7       // right motor
#define RM2 8      // right motor

void setup()
{
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(WS, INPUT);
lcd.begin(20,4);//16 by 2 are the dimensions of the LCD (in number of characters)
Serial.begin(9600);//launch the process of receiving serial data (via bluetooth) at 9600 bits/s
lcd.setCursor(0,0);
lcd.print("Hello World");
delay(2000);
lcd.clear();
}

void loop()
{
  for(int i = 0; i<30000; i++)
  {
  while(Serial.available()){
  lcd.write(Serial.read());//these two lines mean that if there is data coming from the BT module, the Arduino prints it on the LCD.
  }
  delay(1);
  }
  
  r1=digitalRead(room1);
  r2=digitalRead(room2);
  r3=digitalRead(room3);
  if(r1==1 && r2==0 && r3==0)
  {
     while(!(digitalRead(WS)))
           {
            walk();
           }
    delay(300);
    halt();
    delay(2000); 
    cwalk();   
  }
  if(r1==0 && r2==1 && r3==0)
  {
     while(!(digitalRead(WS)))
     {
      walk();
     }
     delay(300);
      while(!(digitalRead(WS)))
     {
       walk();
     }
     delay(300);
     halt();
     delay(2000); 
     cwalk();
  }
  if(r1==1 && r2==1 && r3==0)
  {
     while(!(digitalRead(WS)))
     {
      walk();
     }
     delay(300);
     halt();
     delay(2000);
     while(!(digitalRead(WS)))
     {
       walk();
     }
     delay(300);
     halt();
     delay(2000); 
     cwalk();
  }
  if(r1==0 && r2==0 && r3==1)
  {
     while(!(digitalRead(WS)))
     {
      walk();
     }
     delay(300);
     while(!(digitalRead(WS)))
     {
       walk();
     }
     delay(300);
     while(!(digitalRead(WS)))
     {
       walk();
     }
     delay(300);     
     halt();
     delay(2000); 
     cwalk();
  }
  if(r1==1 && r2==0 && r3==1)
  {
     while(!(digitalRead(WS)))
     {
      walk();
     }
     delay(300);
     halt();
     delay(2000);
     while(!(digitalRead(WS)))
     {
       walk();
     }
     delay(300);
     while(!(digitalRead(WS)))
     {
       walk();
     }
     delay(300);     
     halt();
     delay(2000); 
     cwalk();
  }
  if(r1==0 && r2==1 && r3==1)
  {
     while(!(digitalRead(WS)))
     {
      walk();
     }
     delay(300);
     while(!(digitalRead(WS)))
     {
       walk();
     }
     delay(300);
     halt();
     delay(2000); 
     while(!(digitalRead(WS)))
     {
       walk();
     }
     delay(300);     
     halt();
     delay(2000); 
     cwalk();
  }
  if(r1==1 && r2==1 && r3==1)
  {
     while(!(digitalRead(WS)))
     {
      walk();
     }
     delay(300);
     halt();
     delay(2000);
     while(!(digitalRead(WS)))
     {
       walk();
     }
     delay(300);
     halt();
     delay(2000); 
     while(!(digitalRead(WS)))
     {
       walk();
     }
     delay(300);     
     halt();
     delay(2000); 
     cwalk();
  }  
  while(1); 
}

void halt()
{
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
}

void walk()
{
  tempR = digitalRead(RS);
  tempL = digitalRead(LS);

  if(!(tempL) && !(tempR))     // Move Forward
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }
  
  if(tempL && !(tempR))  // Turn right
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }
  
  if(!(tempL) && tempR)  // turn left
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
  
  if(tempL && tempR)     // stop
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
}

void cwalk()
{
  while(1)
  {
  tempR = digitalRead(RS);
  tempL = digitalRead(LS);

  if(!(tempL) && !(tempR))     // Move Forward
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }
  
  if(tempL && !(tempR))  // Turn right
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }
  
  if(!(tempL) && tempR)  // turn left
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
  
  if(tempL && tempR)     // stop
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
  }
}
