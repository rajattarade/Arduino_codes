#include <Adafruit_NeoPixel.h>

#define PIN 11

Adafruit_NeoPixel strip = Adafruit_NeoPixel(72, PIN, NEO_GRB + NEO_KHZ800);

int startTime = 0;
int currentTime = 0;
int r = 255;
int g = 76;
int b = 2;

void setup() {
strip.begin();
strip.show(); // Initialize all pixels to ‘off’
startTime = millis();
}

void loop() {

for(int x = 0; x <72; x++)
{
int flicker = random(0,90);
int r1 = r-flicker;
int g1 = g-flicker;
int b1 = b-flicker;
if(g1<0) g1=0;
if(r1<0) r1=0;
if(b1<0) b1=0;
strip.setPixelColor(x,r1,g1, b1);
}
currentTime = millis();

if ( (currentTime - startTime) > random(100,150))
{
  strip.show();
  startTime = currentTime;
}

}
