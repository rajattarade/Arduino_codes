#include <Adafruit_NeoPixel.h>

#define PIN        11 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 72 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  pixels.setPixelColor(i, pixels.ColorHSV(hue));

}
