#define S1 2
#define S5 3
#define S4 4
#define soap 5
#define water 6
#define startButton 10
/*
*****
HIGH == valve Close / Pump Off
LOW == relay ON ==> supply goes :- valve Open / Pump ON
*/

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(S1, OUTPUT);
  pinMode(S4, OUTPUT);
  pinMode(S5, OUTPUT);
  pinMode(soap, OUTPUT);
  pinMode(water, OUTPUT);
  pinMode(startButton, INPUT_PULLUP);
  digitalWrite(S1, HIGH);
  digitalWrite(S4, HIGH);
  digitalWrite(S5, HIGH);
  digitalWrite(soap, HIGH);
  digitalWrite(water, HIGH);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(S1, LOW);
  digitalWrite(S4, HIGH);
  digitalWrite(S5, HIGH);
 delay(10000);
   digitalWrite(S1, LOW);
  digitalWrite(S4, HIGH);
  digitalWrite(S5, LOW);
   delay(2000);
  digitalWrite(S1, HIGH);
  digitalWrite(S4, HIGH);
  digitalWrite(S5, LOW);
 delay(10000);
while(1);
  
   
}

