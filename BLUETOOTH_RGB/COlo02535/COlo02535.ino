#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

SoftwareSerial mySerial(5, 4); //Define PIN11 & PIN12 as RX and TX pins


#define LED_PIN 11
#define COLOR_ORDER GRB
#define NUM_LEDS 144
int whiteLed = 0;
#define outputA 6
#define outputB 7
#define color_button 8
 #define RL 12
 #define GL 10
 #define BL 13

 int aState;
 int aLastState; 
 int color_s = 1;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
 int redInt =0;
 int greenInt = 0;
 int blueInt = 0;
  int h=0,s=0,v=0;
String RGBv = ""; 
String RGB_Previous = "255.255.255"; 
boolean RGB_Completed = false;
boolean chng = false;
boolean effect = false;
String effectname = "";

void setColor(int red, int green, int blue);

void setup() {
  pixels.begin();
  pixels.show();
  Serial.begin(115200);
  mySerial.begin(115200);
  RGBv.reserve(30);
  pinMode(color_button, INPUT_PULLUP);

  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);

  aLastState = digitalRead(outputA);  
 
  pinMode(4, OUTPUT);

  pinMode(RL, OUTPUT);
  pinMode(BL, OUTPUT);
  pinMode(GL, OUTPUT);
  digitalWrite(RL,HIGH);
  digitalWrite(BL,LOW);
  digitalWrite(GL,LOW);
  digitalWrite(4,HIGH);

  digitalWrite(RL,HIGH); 
  for (whiteLed = NUM_LEDS; whiteLed > -1; whiteLed = whiteLed - 1)
  {
   pixels.setPixelColor(whiteLed, pixels.Color(125,0,0));
   pixels.show();
   delay(1);
  }
  digitalWrite(RL,LOW);

  digitalWrite(GL,HIGH); 
  for (whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
   pixels.setPixelColor(whiteLed, pixels.Color(0,125,0));
   pixels.show();
   delay(1);
  }
  digitalWrite(GL,LOW);

  digitalWrite(BL,HIGH);
  for (whiteLed = NUM_LEDS; whiteLed > -1; whiteLed = whiteLed - 1) {
   pixels.setPixelColor(whiteLed, pixels.Color(0,0,125));
   pixels.show();
   delay(1);
  }
  digitalWrite(BL,LOW);

  digitalWrite(RL,HIGH);
  digitalWrite(GL,HIGH);
  digitalWrite(BL,HIGH);
  for (whiteLed = 0; whiteLed < 144; whiteLed = whiteLed + 1) {
   pixels.setPixelColor(whiteLed, pixels.Color(125,125,125));
   pixels.show();
   delay(1);
  }
  digitalWrite(RL,HIGH);
  digitalWrite(GL,LOW);
  digitalWrite(BL,LOW);

  
  for (int i = 125; i > -1; i = i - 1)
  { 
    for (whiteLed = 0; whiteLed < 144; whiteLed = whiteLed + 1)
    {
      pixels.setPixelColor(whiteLed, pixels.Color(i,i,i));
    }
  pixels.show();
  delay(2);
}
Serial.print("READY !!");
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
    digitalWrite(RL,HIGH);
    digitalWrite(BL,LOW);
    digitalWrite(GL,LOW);
    }
   if(color_s==2)
    {
    digitalWrite(RL,LOW);
    digitalWrite(BL,LOW);
    digitalWrite(GL,HIGH);
    }
    if(color_s==3)
    {
    digitalWrite(RL,LOW);
    digitalWrite(BL,HIGH);
    digitalWrite(GL,LOW);
    }
   }

aState = digitalRead(outputA); 
   if (aState != aLastState){
     int Rcounter = redInt; 
     int Gcounter = greenInt;
     int Bcounter = blueInt;   
      if (digitalRead(outputB) != aState) { 
      if(color_s==1)
      { Rcounter= Rcounter+10;
       Rcounter = constrain(Rcounter, 0, 255);}
        if(color_s==2)
      { Gcounter= Gcounter+10;
       Gcounter = constrain(Gcounter, 0, 255);}
        if(color_s==3)
      { Bcounter= Bcounter+10;
       Bcounter = constrain(Bcounter, 0, 255);}
     } else {
         if(color_s==1)
      { Rcounter= Rcounter-10;
       Rcounter = constrain(Rcounter, 0, 255);}
        if(color_s==2)
      { Gcounter= Gcounter-10;
       Gcounter = constrain(Gcounter, 0, 255);}
        if(color_s==3)
      { Bcounter= Bcounter-10;
       Bcounter = constrain(Bcounter, 0, 255);}
     }
     redInt = Rcounter;
     greenInt = Gcounter;
     blueInt = Bcounter;
     setColor(redInt, greenInt, blueInt);

   }
   aLastState = aState;
   
 while(mySerial.available() || (chng == 1))
  {
    char ReadChar = (char)mySerial.read();
 
    if(ReadChar == ')')
    {
      RGB_Completed = true;
    }
    else
    {
      RGBv += ReadChar;
    }
    delay(1);
  }

  if(RGB_Completed){
      Light_RGB_LED();   
      RGB_Previous = RGBv;   
      RGBv = "";
      RGB_Completed = false;      
  }

} 
 
void Light_RGB_LED(){

  int SP1 = RGBv.indexOf(' ');
  int SP2 = RGBv.indexOf(' ', SP1+1);
  int SP3 = RGBv.indexOf(' ', SP2+1);
  String N = RGBv.substring(0, SP1);
  String V = RGBv.substring(SP1+1, SP2);
  String C = RGBv.substring(SP2+1, SP3);
  if((C.toInt()-V.toInt())==786)
  {
    
  if(N=="H")
  h=V.toInt();
  if(N=="S")
  s=V.toInt();
  if(N=="V")
  v=V.toInt();
  
  HSV_to_RGB(h,s,v);
  Serial.print(h);
  Serial.print("  ");
  Serial.print(s);
  Serial.print("  ");
  Serial.println(v);
  
  setColor(redInt,greenInt,blueInt);
}
}

void setColor(int red, int green, int blue)
{ 
  for(whiteLed=0; whiteLed < 145; whiteLed++)
  {
   pixels.setPixelColor(whiteLed, pixels.Color(red,green,blue)); // Moderately bright green color.
  }
 pixels.show();
}

void HSV_to_RGB(float h, float s, float v)
{
  int i,f,p,q,t;
  
  h = max(0.0, min(360.0, h));
  s = max(0.0, min(100.0, s));
  v = max(0.0, min(100.0, v));
  
  s /= 100;
  v /= 100;
  
  if(s == 0) {
    // Achromatic (grey)
    redInt = greenInt = blueInt = round(v*255);
    return;
  }

  h /= 60; // sector 0 to 5
  i = floor(h);
  f = h - i; // factorial part of h
  p = v * (1 - s);
  q = v * (1 - s * f);
  t = v * (1 - s * (1 - f));
  switch(i) {
    case 0:
      redInt = round(255*v);
      greenInt = round(255*t);
      blueInt = round(255*p);
      break;
    case 1:
      redInt = round(255*q);
      greenInt = round(255*v);
      blueInt = round(255*p);
      break;
    case 2:
      redInt = round(255*p);
      greenInt = round(255*v);
      blueInt = round(255*t);
      break;
    case 3:
      redInt = round(255*p);
      greenInt = round(255*q);
      blueInt = round(255*v);
      break;
    case 4:
      redInt = round(255*t);
      greenInt = round(255*p);
      blueInt = round(255*v);
      break;
    default: // case 5:
      redInt = round(255*v);
      greenInt = round(255*p);
      blueInt = round(255*q);
    }
}
