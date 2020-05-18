#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EEPROM.h>

int temp = 0;
int characount = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);
int cursr = 0;
int counter = 0;
unsigned long count = 0;
void setup() {
  lcd.begin(16, 2);
  lcd.print("Anashwar Tech");
  lcd.setCursor(0, 1);
  int val = EEPROM.read(0);
  
   lcd.setCursor(0, 1);
   lcd.print(val);
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Start");
  lcd.setCursor(0, 1);
  lcd.print("Count");
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(10, INPUT_PULLUP);
}

void loop() {
  char key = keypad.getKey();
  start:
  lcd.setCursor(0, 0);
  lcd.print("Start");
  lcd.setCursor(0, 1);
  lcd.print("Count");

  if (cursr == 0)
  {
    lcd.setCursor(14, 1);
    lcd.print(" ");
    lcd.setCursor(14, 0);
    lcd.print("*");
  }
  if (cursr == 1)
  {
    lcd.setCursor(14, 0);
    lcd.print(" ");
    lcd.setCursor(14, 1);
    lcd.print("*");
  }

  if (key == '2')
  {
    cursr = 0;
  }
  if (key == '8')
  {
    cursr = 1;
  }

  if (key == '5')
  {
    if (cursr == 0)
    {
      back:
      delay(100);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press # to start");
      lcd.setCursor(0, 1);
      lcd.print("Press * to exit");
      while(key!='*' || key!='#')
        {
         key = keypad.getKey();
         if(key == '*')
          {
          lcd.clear();
          goto start;
          }
         if(key == '#')
          goto res; 
        }
      res: delay(100);
      key = '1';
      lcd.clear();
      lcd.setCursor(0, 0);
      digitalWrite(13, HIGH);
      lcd.print("Press # to stop");
      while (key != '#')
        key = keypad.getKey();
      delay(100);
      digitalWrite(13, LOW);
      delay(10);
      goto back;
    }
    if (cursr == 1)
    {
      delay(100);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter count");
      /*Keypad coad to type and get count*/
      lcd.setCursor(0, 1);
      while (key != '#')
      {
        key = keypad.getKey();
        if (key)
        {
          if (key == '*')
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Enter count");
            count = count / 10;
            lcd.setCursor(0, 1);
            lcd.print(count);
          }
          if (key != '#' && key != '*')
          {
            temp = key - 48;
            count = ((count * 10) + temp);
            lcd.setCursor(0, 1);
            lcd.print(count);
          }
        }
      }
      lcd.clear();
      
      //SUDO COUNTER
      
      while (counter < count)
      {
        digitalWrite(13, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Count:");
        lcd.print(count);
        lcd.setCursor(0, 1);
        lcd.print(counter);
        if (digitalRead(10) == LOW)
        {
          delay(100);
          while(digitalRead(10) != HIGH);
            counter++;
        }
      }
      lcd.clear();
      counter = 0;
      digitalWrite(13, LOW);
    }

  }
}

