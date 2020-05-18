#include <EEPROM.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("Writing");
  EEPROM.write(0, '1');
  delay(100);
    EEPROM.write(1, '2');
  delay(100);
    EEPROM.write(2, '3');
  delay(100);
    EEPROM.write(3, '4');
  delay(100);
  for (int j = 0; j < 4; j++)
    Serial.print(EEPROM.read(j));
}

void loop() {

}
