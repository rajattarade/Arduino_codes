#include <SoftwareSerial.h>
#include "FastLED.h"

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
CRGB leds[NUM_LEDS];
 int aState;
 int aLastState; 
 int color_s = 1;

 int redInt =0;
 int greenInt = 0;
 int blueInt = 0;

String RGBv = ""; 
String RGB_Previous = "255.255.255"; 
String ON = "ON"; 
String OFF = "OFF"; 
boolean RGB_Completed = false;
boolean chng = false;

void setColor(int red, int green, int blue);

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(125);
  
  mySerial.begin(9600);
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
  leds[whiteLed] = CRGB( 125, 0, 0);
  FastLED.show();
  delay(1);
  }
  digitalWrite(RL,LOW);

  digitalWrite(GL,HIGH); 
  for (whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed] = CRGB( 0, 125, 0);
    FastLED.show();
    delay(1);
  }
  digitalWrite(GL,LOW);

  digitalWrite(BL,HIGH);
  for (whiteLed = NUM_LEDS; whiteLed > -1; whiteLed = whiteLed - 1) {
   leds[whiteLed] = CRGB( 0, 0, 125);
   FastLED.show();
   delay(1);
  }
  digitalWrite(BL,LOW);

  digitalWrite(RL,HIGH);
  digitalWrite(GL,HIGH);
  digitalWrite(BL,HIGH);
  for (whiteLed = 0; whiteLed < 144; whiteLed = whiteLed + 1) {
    leds[whiteLed] = CRGB( 125, 125, 125);
    FastLED.show();
    delay(1);
  }
  digitalWrite(RL,HIGH);
  digitalWrite(GL,LOW);
  digitalWrite(BL,LOW);

  
  for (int i = 125; i > -1; i = i - 1)
  { 
    for (whiteLed = 0; whiteLed < 144; whiteLed = whiteLed + 1)
    {
    leds[whiteLed] = CRGB( i, i, i);  
    }
  FastLED.show();
  delay(2);
  FastLED.setBrightness(125);
}

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

aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){
     int Rcounter = redInt; 
     int Gcounter = greenInt;
     int Bcounter = blueInt;   
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
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
 
    if(ReadChar == ')'){
      RGB_Completed = true;
    }else{
       RGBv += ReadChar;
    }
    delay(1);
  }

  if(RGB_Completed){
      if(RGBv==ON){
          RGBv = RGB_Previous; 
          Light_RGB_LED();
      }else if(RGBv==OFF){
          RGBv = "0.0.0"; 
          Light_RGB_LED();
      }else{
          Light_RGB_LED();   
          RGB_Previous = RGBv;     
      }
      RGBv = "";
      RGB_Completed = false;      
  } 
} 
 
void Light_RGB_LED(){
 
  int SP1 = RGBv.indexOf(' ');
  int SP2 = RGBv.indexOf(' ', SP1+1);
  int SP3 = RGBv.indexOf(' ', SP2+1);
  String R = RGBv.substring(0, SP1);
  String G = RGBv.substring(SP1+1, SP2);
  String B = RGBv.substring(SP2+1, SP3);

 
  setColor(R.toInt(),G.toInt(),B.toInt());

}

void setColor(int red, int green, int blue)
{
  for(whiteLed=0; whiteLed < 145; whiteLed++)
  {
   // leds[whiteLed] = CRGB( red, green, blue); 
  }
  FastLED.show();
}
