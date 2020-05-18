#include "HX711.h"

HX711 scale(D4, D5);

void setup() {

  Serial.begin(9600);

}

void loop() {

  Serial.print(scale.getGram(), 1);
  Serial.println(" g");

  delay(200);
}

