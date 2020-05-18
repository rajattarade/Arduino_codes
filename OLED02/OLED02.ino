#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "HX711.h"

// HX711.DOUT  - pin #A1
// HX711.PD_SCK - pin #A0

HX711 scale(A0, A1);    // parameter "gain" is ommited; the default value 128 is used by the library
float iq,q,iq2,i[50]={};
int count = 0;
float torque = 0;
// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.display();
  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  display.clearDisplay();
  
}

void loop() {
  count++;
  if(count==5)
   count=0;
   
  i[count] = scale.get_units(1);

  for(int a=0;a<5;a++)
  {
    q+=i[a];
  }
  q=q/5;
  
  if(q>(iq+0.10) || q<(iq-0.10))
  {
   iq=q;
  }
  
  if(iq2!=iq)
  {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(27, 30);
  //display.print((((q*9.975)/1000)*9.81)*12);
  display.print(int(q*9.975));
  display.display();
  }
  iq2=iq;
}

