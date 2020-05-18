#include <Wire.h>
//#include <Adafruit_SSD1306.h>
//#include <Adafruit_GFX.h>
#include "HX711.h"

// HX711.DOUT  - pin #A1
// HX711.PD_SCK - pin #A0

HX711 scale(A0, A1);    // parameter "gain" is ommited; the default value 128 is used by the library
float ip,i=0;
// OLED display TWI address
//#define OLED_ADDR   0x3C

//Adafruit_SSD1306 display(-1);

/*#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif*/
int state=0;
void setup() {
  // initialize and clear display
  //display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  //display.display();
  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0
  i = scale.get_units(1);
  ip=i;
    pinMode(2, INPUT_PULLUP);
  //display.clearDisplay();
  Serial.begin(38400);
}

void loop() {
  state = digitalRead(2);
  if(state==LOW)
  {
   scale.tare();
  }
  
  i=scale.get_units();

  if((i)>((ip)+0.5) || (i)<((ip)-0.5) )
  {
   ip=i;
  }

  
  Serial.println(ip*9.7);
  //display.clearDisplay();
  //display.setTextSize(2);
  //display.setTextColor(WHITE);
  //display.setCursor(27, 30);
  //display.print((((ip*5.7)/1000)*9.81)*12);

  //display.print(ip*5.7); 
  
  //display.display();
}

