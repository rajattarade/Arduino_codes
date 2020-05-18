#include "DigiKeyboard.h"
#include <EEPROM.h>
String codes[10]={"25912063",
"28967337",
"33084235",
"42978349",
"48737268",
"49005889",
"63615497",
"86548067",
"94744585",
"97150155",
};

void setup() {
  }

void loop() {
DigiKeyboard.sendKeyStroke(0);
delay(2000);
DigiKeyboard.sendKeyStroke(0);
int count = EEPROM.read(0);
delay(2000);
DigiKeyboard.println(codes[(int(EEPROM.read(0)))%10]);
EEPROM.write(0, count+1);
while(1);
}
