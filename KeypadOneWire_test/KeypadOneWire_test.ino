//This sketch displays the values on a scale of 0-1023 that are generated when you press each key
//They should be similar to the values I have given in the Instructable 
//(allowing for small variations in tolerance of the resistors)


#include <Stepper.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

int keyboardPin = 0;    // Analog input pin that the keypad is attached to
 int keyboardValue = 0;   // value read from the keyboard


 void setup() {
   // initialize serial communications at 9600 bps:
      lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  delay(2000);
  lcd.clear();

 }

 void loop() {
   keyboardValue = analogRead(keyboardPin); // read the pot value
  
   lcd.print(keyboardValue);      // print the value back to the serial view window on your PC
   delay(1000);                     // wait 1000 milliseconds before the next loop
   lcd.clear();
 }


