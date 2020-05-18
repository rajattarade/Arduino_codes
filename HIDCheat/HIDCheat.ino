#include "DigiKeyboard.h"

void setup()
{
  
}

void loop()
{
  int val = analogRead(A0);

  if(val<150)
  {
   DigiKeyboard.sendKeyStroke(0);
   DigiKeyboard.print(" ");
   }
 DigiKeyboard.delay(10);
}

