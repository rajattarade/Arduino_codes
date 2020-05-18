#include <SoftwareSerial.h>
#include "FastLED.h"

#define NUM_LEDS 144
#define LED_PIN 11
#define COLOR_ORDER GRB
 
CRGB leds[NUM_LEDS];

SoftwareSerial Bluetooth(5, 4); // Arduino(RX, TX) - Bluetooth (TX, RX)

// Initial background color 
int backR = 0;
int backG = 0;
int backB = 0;

// Initial reactive color 
int reactiveR = 0;
int reactiveG = 0;
int reactiveB = 0;

int brightness = 50; // Initial brightness

String dataIn = "";

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  Serial.begin(9600);
  Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
    for (int whiteLed = NUM_LEDS; whiteLed > -1; whiteLed = whiteLed - 1) {
    leds[whiteLed] = CRGB::Red;
    FastLED.show();
    delay(1);
    leds[whiteLed] = CRGB::Black;
  }

  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed] = CRGB::Green;
    FastLED.show();
    delay(1);
    leds[whiteLed] = CRGB::Black;
  }

  for (int whiteLed = NUM_LEDS; whiteLed > -1; whiteLed = whiteLed - 1) {
    leds[whiteLed] = CRGB::Blue;
    FastLED.show();
    delay(1);
    leds[whiteLed] = CRGB::Black;
  }

  for (int whiteLed = 0; whiteLed < 144; whiteLed = whiteLed + 1) {
    leds[whiteLed] = CRGB::White;
    FastLED.show();
    delay(1);
  }
  FastLED.show();

  for (int i = brightness; i > -1; i = i - 1) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(20);
  }
}

void loop() {
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.readString();
    Serial.println(dataIn);
    delay(20);
    if (dataIn.startsWith("1")) {
      delay(10);
      String stringR = dataIn.substring(dataIn.indexOf("R") + 1, dataIn.indexOf("G"));
      reactiveR = stringR.toInt();
      String stringG = dataIn.substring(dataIn.indexOf("G") + 1, dataIn.indexOf("B"));
      reactiveG = stringG.toInt();
      String stringB = dataIn.substring(dataIn.indexOf("B") + 1, dataIn.indexOf("E"));
      reactiveB = stringB.toInt();
    }
    else if (dataIn.startsWith("2")) {
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
  
  Serial.print(backR);
  Serial.print(", ");
  Serial.print(backG);
  Serial.print(", ");
  Serial.print(backB);
  Serial.println(", ");
  
  for (int pinNo = 0; pinNo <= NUM_LEDS; pinNo++) {
    leds[pinNo] = CRGB( backR, backG, backB);
  }
  
  FastLED.show();
  delay(20);
}
