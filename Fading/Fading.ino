int ledPin = 11;    // LED connected to digital pin 9


void setup() {
  // nothing happens in setup
}

void loop() {
//  // fade in from min to max in increments of 5 points:
//  for (int fadeValue = 0 ; fadeValue <= 190; fadeValue++)
//  {
//    analogWrite(ledPin, fadeValue);
//    delay(12);
//  }
//  for (int fadeValue = 190 ; fadeValue >= 0; fadeValue--)
//  {
//    analogWrite(ledPin, fadeValue);
//    delay(10);
//  }

  for (int fadeValue = 0 ; fadeValue <= 50; fadeValue++)
  {
    analogWrite(ledPin, fadeValue);
    delay(25);
  }
  for (int fadeValue = 50 ; fadeValue >= 0; fadeValue--)
  {
    analogWrite(ledPin, fadeValue);
    delay(10);
  }
  delay(200);

  for (int fadeValue = 0 ; fadeValue <= 50; fadeValue++)
  {
    analogWrite(ledPin, fadeValue);
    delay(25);
  }
  for (int fadeValue = 50 ; fadeValue >= 0; fadeValue--)
  {
    analogWrite(ledPin, fadeValue);
    delay(10);
  }
  
  delay(2000);
  
}


