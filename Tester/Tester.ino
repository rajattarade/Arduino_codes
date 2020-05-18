#define S1 2
#define S5 3
#define S4 4
#define soapPump 5
#define waterPump 6
#define startButton 10


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(S1, OUTPUT);
  pinMode(S4, OUTPUT);
  pinMode(S5, OUTPUT);
  pinMode(soapPump, OUTPUT);
  pinMode(waterPump, OUTPUT);
  pinMode(startButton, INPUT_PULLUP);
  digitalWrite(S1, HIGH);
  digitalWrite(S4, LOW);
  digitalWrite(S5, HIGH);
  digitalWrite(soapPump, HIGH); //Pump OFF
  digitalWrite(waterPump, LOW);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available())
  {
    int state = Serial.parseInt();
    if (state == 1)
    {
      digitalWrite(S1, HIGH);
      digitalWrite(S5, HIGH);
      delay(100);
      digitalWrite(S4, LOW);
      delay(1000);
      digitalWrite(soapPump, LOW);
      Serial.println("Pump ON");
    }
    if (state == 2)
    {
      digitalWrite(soapPump, HIGH);
      delay(1000);
      digitalWrite(S4, HIGH);
      Serial.println("Pump OFF");
    }
  }
}
