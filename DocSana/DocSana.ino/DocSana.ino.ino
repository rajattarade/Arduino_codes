#include "HX711.h"
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(11, 12, 5, 6, 7, 8);
// HX711.DOUT	- pin #A1
// HX711.PD_SCK	- pin #A0
const byte interruptPin = 2;
HX711 scale(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library
float a =0;
float pa =0;

void setup() {

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
  
  Serial.begin(38400);
  Serial.println("HX711 Demo");
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1000);
  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided 
						// by the SCALE parameter (not set yet)  

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
						// by the SCALE parameter set with set_scale

  Serial.println("Readings:");

  a = -(scale.get_units(2));
  pa = a;
  lcd.print(a);
  lcd.setCursor(0, 0);
  lcd.print("DONE...!!");
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 1);
  a = -(scale.get_units(2));
  if(pa<a)
  {
  pa = a;
  lcd.clear();
  lcd.print(a);
  }
}

void blink() {
 scale.tare();
 lcd.clear();
 a = -(scale.get_units(2));
 pa = a;
 lcd.print(a);
  
}
