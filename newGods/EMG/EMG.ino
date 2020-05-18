#include "Filter.h"

//Global Variables
ExponentialFilter<long> ADCFilter1(100, 0);
ExponentialFilter<long> ADCFilter2(100, 0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int filtered1 = 0;
  int filtered2 = 0;


  ADCFilter1.Filter(analogRead(A0));
  filtered1 = ADCFilter1.Current();
  ADCFilter2.Filter(analogRead(A1));
  filtered2 = ADCFilter2.Current();
 
  Serial.print(filtered1);
  Serial.print(","); 
  Serial.println(filtered2);

//  Serial.print(constrain(map(filtered1,-600,600,0,1023),0,1023));
//  Serial.print(","); 
//  Serial.println(constrain(map(filtered2,-2500,2500,0,1023),0,1023));
}
