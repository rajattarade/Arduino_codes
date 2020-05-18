#include <Stepper.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, A5, A4, A3, A2);

int keypressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard
int temp=0;

void setup() {
  // put your setup code here, to run once:
    myStepper.setSpeed(60);
    Serial.begin(9600);  //hardware serial to PC
      lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Stepper Motor");
  lcd.setCursor(0, 1);  
  lcd.print("Controller");
  delay(2000);
  lcd.clear();
  }

void loop() {
  int count=0;
  int dir=0;
  // put your main code here, to run repeatedly:
lcd.setCursor(0, 0);  
lcd.print("1. Step mode");
lcd.setCursor(0, 1); 
lcd.print("2. Speed mode");

 keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
 while (keyboardValue < 25)
 {
 keyboardValue = analogRead(keyboardPin); 
 delay(50);
 }
 readkeyboard();
 if(keypressed==1)
 {
    lcd.clear();
    lcd.setCursor(0, 0);  
    lcd.print("Enter Steps");
    lcd.setCursor(0, 1);
   delay(500);
   count=100;
   dir=0;
   while(count!=0)
   {
    keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
    while (keyboardValue < 25)
    {
     keyboardValue = analogRead(keyboardPin); 
     delay(50);
    }
   readkeyboard();
   if(keypressed==30)
   dir=1;
   else
   {
   temp=(keypressed*count)+temp;
   count=count/10;
   }
   }
   if(dir==0)
   {
   Serial.println(temp);
   myStepper.step(temp);
   }
   if(dir==1)
   {
   Serial.print('-');
   Serial.println(temp);
   myStepper.step(-temp);   
   }
   
   delay(500);
   temp=0;
   digitalWrite(A5,LOW);
   digitalWrite(A4,LOW);
   digitalWrite(A3,LOW);
   digitalWrite(A2,LOW);
 }
 if(keypressed==2)
 {
   lcd.clear();
   lcd.setCursor(0, 0);  
   lcd.print("Enter Speed in");
   lcd.setCursor(0, 1);  
   lcd.print("RPM : ");
   delay(500);
   count=100;
   dir=0;
   while(count!=0)
   {
    keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
    while (keyboardValue < 25)
    {
     keyboardValue = analogRead(keyboardPin); 
     delay(50);
    }
   readkeyboard();
   if(keypressed==30)
   dir=1;
   else
   {
   temp=(keypressed*count)+temp;
   count=count/10;
   }
   }
   if(dir==0)
   {
   Serial.println(temp);
    myStepper.setSpeed(temp);
    while(1)
    {
    myStepper.step(200);
    }
   }
   if(dir==1)
   {
   Serial.print('-');
   Serial.println(temp);
   myStepper.setSpeed(temp);
   while(1)
   myStepper.step(-200);
   }
   
   delay(500);
   temp=0; 
 }                            
}

void readkeyboard()
{
   keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
   if (keyboardValue <175){keypressed = 10;}
   if ((keyboardValue >175) && (keyboardValue < 224)){keypressed = 7;}
   if ((keyboardValue >224) && (keyboardValue < 284)){keypressed = 0;}
   if ((keyboardValue >284) && (keyboardValue < 330)){keypressed = 8;}
   if ((keyboardValue >330) && (keyboardValue < 381)){keypressed = 30;}
   if ((keyboardValue >381) && (keyboardValue < 502)){keypressed = 9;}
   if ((keyboardValue >502) && (keyboardValue < 657)){keypressed = 4;}
   if ((keyboardValue >657) && (keyboardValue < 769)){keypressed = 5;}
   if ((keyboardValue >769) && (keyboardValue < 843)){keypressed = 6;}
   if ((keyboardValue >843) && (keyboardValue < 906)){keypressed = 1;}
   if ((keyboardValue >906) && (keyboardValue < 951)){keypressed = 2;}
   if ((keyboardValue >951) && (keyboardValue < 995)){keypressed = 3;}
   if (keyboardValue >995){keypressed = 3;}
  //NOTE: the values used above are all halfway between the value obtained with each keypress in previous test sketch 
   
   while (keyboardValue > 25) {
     delay (100);
     keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
   }//wait until key no longer being pressed before continuing
     
   
   if(keypressed==30)
   lcd.print('-');
   else
   lcd.print(keypressed);      // print the value back to the Serial view window on your PC
   delay(1000);                     // wait 1000 milliseconds before the next loop
}

