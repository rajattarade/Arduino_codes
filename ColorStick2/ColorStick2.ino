#include <SoftwareSerial.h>
#include "FastLED.h"

#define NUM_LEDS 144
#define LED_PIN 11
#define COLOR_ORDER GRB
#define outputA 6
#define outputB 7
#define color_button 8
 #define RL 12
 #define GL 10
 #define BL 13
 
 int aState;
 int aLastState; 
 int color_s = 1;

CRGB leds[NUM_LEDS];

SoftwareSerial Bluetooth(5, 4); // Arduino(RX, TX) - Bluetooth (TX, RX)

// Initial background color 
int backR = 1;
int backG = 1;
int backB = 1;

int brightness = 50; // Initial brightness

String dataIn = "";

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  Serial.begin(9600);
  Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
  
  pinMode(color_button, INPUT_PULLUP);
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  aLastState = digitalRead(outputA);  
  pinMode(RL, OUTPUT);
  pinMode(BL, OUTPUT);
  pinMode(GL, OUTPUT);

  digitalWrite(RL,HIGH);
  for (int whiteLed = NUM_LEDS; whiteLed > -1; whiteLed = whiteLed - 1)
  {
    leds[whiteLed] = CRGB::Red;
    FastLED.show();
    delay(1);
  }
  digitalWrite(RL,LOW);

  digitalWrite(GL,HIGH);
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed] = CRGB( 0, 255, 0);
    FastLED.show();
    delay(1);
  }
  digitalWrite(GL,LOW);

  digitalWrite(BL,HIGH);
  for (int whiteLed = NUM_LEDS; whiteLed > -1; whiteLed = whiteLed - 1) {
    leds[whiteLed] = CRGB( 0, 0, 255);
    FastLED.show();
    delay(1);
  }
  digitalWrite(BL,LOW);


  digitalWrite(RL,HIGH);
  digitalWrite(GL,HIGH);
  digitalWrite(BL,HIGH);
  for (int whiteLed = 0; whiteLed < 144; whiteLed = whiteLed + 1) {
    leds[whiteLed] = CRGB( 255, 255, 255);
    FastLED.show();
    delay(1);
  }
  digitalWrite(RL,HIGH);
  digitalWrite(GL,LOW);
  digitalWrite(BL,LOW);
  
  for (int i = brightness; i > -1; i = i - 1) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(20);
  }

  for (int whiteLed = 0; whiteLed < 144; whiteLed = whiteLed + 1) {
    leds[whiteLed] = CRGB( 0, 0, 0);
    FastLED.show();
    delay(1);
  }
FastLED.setBrightness(brightness);
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
   
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.readString();
    delay(20);
    if (dataIn.startsWith("2")) {
      String stringR = dataIn.substring(dataIn.indexOf("R") + 1, dataIn.indexOf("G"));
      backR = stringR.toInt();
      String stringG = dataIn.substring(dataIn.indexOf("G") + 1, dataIn.indexOf("B"));
      backG = stringG.toInt();
      String stringB = dataIn.substring(dataIn.indexOf("B") + 1, dataIn.indexOf("E"));
      backB = stringB.toInt();
    }
    else if (dataIn.startsWith("3")) {
      String stringBrightness = dataIn.substring(dataIn.indexOf("3") + 1, dataIn.length());
      brightness = stringBrightness.toInt();
      FastLED.setBrightness(brightness);
    }
  }
  
    for (int pinNo = 0; pinNo <= NUM_LEDS; pinNo++)
  {
    leds[pinNo] = CRGB( backR, backG, backB);
  }
  FastLED.show();
  delay(20);

}
