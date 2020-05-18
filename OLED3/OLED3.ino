
#include "HX711.h"

#define DOUT  A0
#define CLK  A1

HX711 scale(DOUT, CLK);

float calibration_factor = -12200; //=100g
float output;
int readIndex;
float total=0;
float average=0;
float average_last=0;
const int cycles=20;
float readings[cycles];

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  output=scale.get_units(), 2;
  Serial.print(output);


//Smoothing the results
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the scale
  readings[readIndex] = scale.get_units(), 2;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= cycles) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / cycles;

  average=scale.get_units(), 2;


//Zero drift compensation
  if((average_last>average+0.10 || average_last<average-0.10)){
      //Minimum Load defines Zero-Band
      if (average<0.06){average=0;}
      Serial.print("\tFilter: ");
      Serial.print(average*35.5);
      average_last=average;
  }
  else{
    Serial.print("\tFilter: ");
    Serial.print(average_last*35.5);
  }
  Serial.print(" g"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
}
