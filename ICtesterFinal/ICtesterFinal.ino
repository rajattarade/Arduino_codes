#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

int andc = 0;
int orc = 0;
int nandc = 0;
int xorc = 0;


LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0x27);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  andc = 0;
  orc = 0;
  nandc = 0;
  xorc = 0;
  lcd.begin(16, 2); // initialize the lcd
}

void loop() {
  lcd.setBacklight(255);
  lcd.home(); lcd.clear();
  lcd.print("Working...");
  Serial.print("Working...");
  Serial.println();

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);

  delay(100);
  if ((!digitalRead(4)) && (!digitalRead(5)) && (!digitalRead(7)) && (!digitalRead(6)))
  {
    andc++;
    orc++;
    xorc++;
  }
  if ((digitalRead(4)) && (digitalRead(5)) && (digitalRead(7)) && (digitalRead(6)))
  {
    nandc++;
  }

  //////////////////////////////////////////
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);

  delay(100);
  if ((!digitalRead(4)) && (!digitalRead(5)) && (!digitalRead(7)) && (!digitalRead(6)))
  {
    andc++;
  }
  if ((digitalRead(4)) && (digitalRead(5)) && (digitalRead(7)) && (digitalRead(6)))
  {
    orc++;
    nandc++;
    xorc++;
  }
  //////////////////////////////////////////
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);

  delay(100);
  if ((!digitalRead(4)) && (!digitalRead(5)) && (!digitalRead(7)) && (!digitalRead(6)))
  {
    andc++;
  }
  if ((digitalRead(4)) && (digitalRead(5)) && (digitalRead(7)) && (digitalRead(6)))
  {
    orc++;
    nandc++;
    xorc++;
  }
  //////////////////////////////////////////
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);

  delay(100);
  if ((!digitalRead(4)) && (!digitalRead(5)) && (!digitalRead(7)) && (!digitalRead(6)))
  {
    nandc++;
    xorc++;
  }
  if ((digitalRead(4)) && (digitalRead(5)) && (digitalRead(7)) && (digitalRead(6)))
  {
    andc++;
    orc++;
  }

  if (andc == 4)
  {
    Serial.print("7408 : PASS");
    lcd.home(); lcd.clear();
    lcd.print("7408 : PASS");
  }


  else if (orc == 4)
  { Serial.print("7432 : PASS");
    lcd.home(); lcd.clear();
    lcd.print("7432 : PASS");
  }

  else if (nandc == 4)
  { Serial.print("7400 : PASS");
    lcd.home(); lcd.clear();
    lcd.print("7400 : PASS");
  }

  else if (xorc == 4)
  { Serial.print("7486 : PASS");
    lcd.home(); lcd.clear();
    lcd.print("7486 : PASS");
  }

  else
  { Serial.print("Unknown");
    lcd.home(); lcd.clear();
    lcd.print("Unknown");
  }

  while (1);

}
