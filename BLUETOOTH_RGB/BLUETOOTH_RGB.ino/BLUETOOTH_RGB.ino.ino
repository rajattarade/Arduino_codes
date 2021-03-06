#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,7); //Define PIN11 & PIN12 as RX and TX pins

int PIN_RED = 10;
int PIN_GREEN = 11;
int PIN_BLUE = 9;

 #define RL A5
 #define GL A4
 #define BL A3
 
 #define outputA 3
 #define outputB 4
 #define color_button 2

 int aState;
 int aLastState; 
 int color_s = 1;

 int redInt =0;
 int greenInt = 0;
 int blueInt = 0;

String RGB = ""; 
String RGB_Previous = "255.255.255"; 
String ON = "ON"; 
String OFF = "OFF"; 
boolean RGB_Completed = false;
boolean chng = false;

 
void setup() {
  pinMode (PIN_RED, OUTPUT);
  pinMode (PIN_GREEN, OUTPUT);
  pinMode (PIN_BLUE, OUTPUT);
  Serial.begin(9600); 
  mySerial.begin(9600);
  RGB.reserve(30);
  pinMode(color_button, INPUT_PULLUP);
  
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);

   aLastState = digitalRead(outputA);  
 
  pinMode(4, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(RL, OUTPUT);
  pinMode(BL, OUTPUT);
  pinMode(GL, OUTPUT);
  digitalWrite(RL,LOW);
  digitalWrite(BL,HIGH);
  digitalWrite(GL,HIGH);
  digitalWrite(4,HIGH);
  setColor(255, 0, 0);
  delay(500);
  setColor(0, 255, 0);
  delay(500);
  setColor(0, 0, 255);
  delay(500);
  setColor(255, 255, 255);
  delay(500);
  setColor(0, 0, 0);
  
}
 
void loop() {
   if(!digitalRead(color_button))
   { 
    delay(500);
    Serial.print("Colour selected : ");
    color_s++;
    if(color_s>3)
    color_s=1;
    Serial.println(color_s);
    if(color_s==1)
    {
    digitalWrite(RL,LOW);
    digitalWrite(BL,HIGH);
    digitalWrite(GL,HIGH);
    }
   if(color_s==2)
    {
    digitalWrite(RL,HIGH);
    digitalWrite(BL,HIGH);
    digitalWrite(GL,LOW);
    }
    if(color_s==3)
    {
    digitalWrite(RL,HIGH);
    digitalWrite(BL,LOW);
    digitalWrite(GL,HIGH);
    }
   }

aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){
     int Rcounter = redInt; 
     int Gcounter = greenInt;
     int Bcounter = blueInt;   
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
      if(color_s==1)
      { Rcounter= Rcounter-10;
       Rcounter = constrain(Rcounter, 0, 255);}
        if(color_s==2)
      { Gcounter= Gcounter-10;
       Gcounter = constrain(Gcounter, 0, 255);}
        if(color_s==3)
      { Bcounter= Bcounter-10;
       Bcounter = constrain(Bcounter, 0, 255);}
     } else {
         if(color_s==1)
      { Rcounter= Rcounter+10;
       Rcounter = constrain(Rcounter, 0, 255);}
        if(color_s==2)
      { Gcounter= Gcounter+10;
       Gcounter = constrain(Gcounter, 0, 255);}
        if(color_s==3)
      { Bcounter= Bcounter+10;
       Bcounter = constrain(Bcounter, 0, 255);}
     }
     Serial.print("Position: ");
     Serial.print(Rcounter);
     Serial.print(" : ");
     Serial.print(Gcounter);
     Serial.print(" : ");
     Serial.println(Bcounter);
     redInt = Rcounter;
     greenInt = Gcounter;
     blueInt = Bcounter;
     setColor(redInt, greenInt, blueInt);

   }
   aLastState = aState;

   
   
  while(mySerial.available() || (chng == 1))
  {
    char ReadChar = (char)mySerial.read();
 
    if(ReadChar == ')'){
      RGB_Completed = true;
    }else{
       RGB += ReadChar;
    }
  }
  
  if(RGB_Completed){
 
      Serial.print("RGB:");
      Serial.print(RGB);
      Serial.print("     PreRGB:");
      Serial.println(RGB_Previous);
      
      if(RGB==ON){
          RGB = RGB_Previous; 
          Light_RGB_LED();
      }else if(RGB==OFF){
          RGB = "0.0.0"; 
          Light_RGB_LED();
      }else{
          Light_RGB_LED();   
          RGB_Previous = RGB;     
      }
      RGB = "";
      RGB_Completed = false;      
  } 
} 
 
void Light_RGB_LED(){
 
  int SP1 = RGB.indexOf(' ');
  int SP2 = RGB.indexOf(' ', SP1+1);
  int SP3 = RGB.indexOf(' ', SP2+1);
  String R = RGB.substring(0, SP1);
  String G = RGB.substring(SP1+1, SP2);
  String B = RGB.substring(SP2+1, SP3);

 
  setColor(R.toInt(),G.toInt(),B.toInt());
}

void setColor(int red, int green, int blue)
{ Serial.print("R=");
  Serial.println(red);
  Serial.print("G=");
  Serial.println(green);
  Serial.print("B=");
  Serial.println(blue);
  analogWrite(PIN_RED,  red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE,  blue);
}
