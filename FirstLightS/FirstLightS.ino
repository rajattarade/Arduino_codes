#include "FastLED.h"
#define NUM_LEDS 144
#define DATA_PIN 11
#define Brightness 100
CRGB leds[NUM_LEDS];

void setup() {
  delay(1000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(Brightness);
}

void loop() {
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

  for (int i = Brightness; i > -1; i = i - 1) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(20);
  }

  while (1);
}
