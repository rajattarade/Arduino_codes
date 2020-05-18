#include "HX711.h"
#include "Filter.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

//Global Variables
int sensorPin = 0;          //pin number to use the ADC
long sensorValue = 0;        //initialization of sensor variable, equivalent to EMA Y
HX711 scale(A1, A0);    // parameter "gain" is ommited; the default value 128 is used by the library
float ip = 0;
float torque = 0;
ExponentialFilter<long> ADCFilter(15, 0);
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

void setup() {
  pinMode(2, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.display();
  scale.read_average(25);
  scale.tare();
  display.clearDisplay();
}

void loop() {
  int grams = 0;
  float torque = 0;
  int state = digitalRead(2);
  if (state == LOW)
  {
    scale.tare();
  }

  sensorValue = scale.get_units(1);      //read the sensor value using ADC
  sensorValue = sensorValue / 165;
 

  ADCFilter.Filter(sensorValue);
  grams = ADCFilter.Current();

  if ((grams) > ((ip) + 2) || (grams) < ((ip) - 2) )
  {
    ip = grams;
  }
  torque = ((((ip * 5.7) / 1000) * 9.81) * 12) / 6.6;
  if (torque < 0)
    torque = 0;
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  display.print(torque,1);
  display.print(" N.Cm"); 
  display.display();

}
