#include <EEPROM.h>

int a = 0;
int value;

void setup()
{
  Serial.begin(9600);
}

void loop()
{ 
  
  value = EEPROM.read(a);
  
/*  if(value>10)
  {
  printf("BLOCK FOREVER");
  delay(100);
  while(1);
  }
 /* value = EEPROM.read(a);
  value = value+1;
  EEPROM.write(a, value);
  value = EEPROM.read(a);
*/EEPROM.write(a, 0);
  Serial.print(a);
  Serial.print("\t");
  Serial.print(value);
  Serial.println();

  while(1);
}

