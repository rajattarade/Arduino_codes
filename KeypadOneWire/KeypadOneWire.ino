int keypressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard

void setup(){
  
  
  Serial.begin(9600);  //hardware serial to PC
  
}


void loop(){
 
 
 keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
 while (keyboardValue < 25){
   //do nothing until a key is pressed
 keyboardValue = analogRead(keyboardPin); 
 delay(50);
                            }//end of do nothing till a key is pressed
                            
                            
 readkeyboard(); //get the value of key being pressed "keypressed" i.e. 0-9
 
}



//read the keyboard routine
void readkeyboard(){
   keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
   if (keyboardValue <167){keypressed = 1;}
   if ((keyboardValue >167) && (keyboardValue < 222)){keypressed = 4;}
   if ((keyboardValue >222) && (keyboardValue < 268)){keypressed = 2;}
   if ((keyboardValue >268) && (keyboardValue < 345)){keypressed = 5;}
   if ((keyboardValue >345) && (keyboardValue < 364)){keypressed = 3;}
   if ((keyboardValue >364) && (keyboardValue < 449)){keypressed = 6;}
   if ((keyboardValue >449) && (keyboardValue < 577)){keypressed = 10;}
   if ((keyboardValue >577) && (keyboardValue < 717)){keypressed = 0;}
   if ((keyboardValue >717) && (keyboardValue < 800)){keypressed = 30;}
   if ((keyboardValue >800) && (keyboardValue < 862)){keypressed = 7;}
   if ((keyboardValue >862) && (keyboardValue < 920)){keypressed = 8;}
   if ((keyboardValue >920) && (keyboardValue < 947)){keypressed = 9;}
   if (keyboardValue >947){keypressed = 9;}
  //NOTE: the values used above are all halfway between the value obtained with each keypress in previous test sketch 
   
   while (keyboardValue > 25) {
     delay (100);
     keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
   }//wait until key no longer being pressed before continuing
     
   
   
   Serial.println(keypressed);      // print the value back to the Serial view window on your PC
   delay(1000);                     // wait 1000 milliseconds before the next loop
                     }
   //end of read the keyboard routine

