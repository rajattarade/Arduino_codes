/* @file EventSerialKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates using the KeypadEvent.
  || #
*/
#include <Keypad.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(A0, 2, 3, 4, 5, 6); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {7, 8, 9, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 12, 13}; //connect to the column pinouts of the keypad
byte typepass[4] = {};
byte password[4] = {'1', '1', '2', '2'};
int line = 0;
boolean linestate[4] = {false, false, false, false};
int relay[4] = {A1, A2, A3, A4};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display }
  Serial.begin(9600);
  for(int i = 0; i < 4;i++)
  {
   pinMode(relay[i], OUTPUT);  
  }
}

void loop() {
  
  for(int i = 0; i < 4;i++)
  {
   digitalWrite(relay[i], !linestate[i]);  
  }
  
  lcd.setCursor(0, 0);
  lcd.print("L-1");
  lcd.setCursor(4, 0);
  if (linestate[0] == true)
    lcd.print("ON ");
  else
    lcd.print("OFF");

  lcd.setCursor(9, 0);
  lcd.print("L-2");
  lcd.setCursor(13, 0);
  if (linestate[1] == true)
    lcd.print("ON ");
  else
    lcd.print("OFF");

  lcd.setCursor(0, 1);
  lcd.print("L-3");
  lcd.setCursor(4, 1);
  if (linestate[2] == true)
    lcd.print("ON ");
  else
    lcd.print("OFF");

  lcd.setCursor(9, 1);
  lcd.print("L-4");
  lcd.setCursor(13, 1);
  if (linestate[3] == true)
    lcd.print("ON ");
  else
    lcd.print("OFF");

  char key = keypad.getKey();
  delay(100);
  //  while(~key)
  //  {
  //   key = keypad.getKey();
  //  }
  if (key) {
    if (key == '1' || key == '2' || key == '3' || key == '4')
    {
      line = int(key) - 48;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("L-");
      lcd.print(key);
      lcd.print(" IS ");
      if (linestate[line-1] == true)
        lcd.print("ACTIVE");
      else
        lcd.print("DOWN");
      lcd.setCursor(0, 1);
      lcd.print("PASSWORD :");
      key = NULL;
      for (int i = 0; i < 4; i++)
      {
        while (key == NO_KEY)
          key = keypad.getKey();
        typepass[i] = key;
        key = NULL;
        lcd.print("*");
      }
      int c = 0;
      for (int i = 0; i < 4; i++)
      {
        if (typepass[i] == password[i])
          c++;
      }
      if (c == 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LINE ");
        lcd.print(line);
        lcd.setCursor(0, 1);
        lcd.print("TOGGLED");
        linestate[line - 1] = !linestate[line - 1];
        delay(2000);
        lcd.clear();
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wrong Password");
        delay(2000);
        lcd.clear();
      }
    }
  }
}
