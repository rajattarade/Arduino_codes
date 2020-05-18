
int val;
int encoder0PinA = 3;
int encoder0PinB = 4;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;
int setPoint = 0;
int input = 0;


#define motorPin0 9
#define motorPin1 10


void setup() {
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  pinMode (motorPin0, OUTPUT);
  pinMode (motorPin1, OUTPUT);
  Serial.begin (9600);
}

void loop() {
  input = analogRead(A0);
  if (input > 512)
  input = 512;
  Serial.print("Input Angle : ");
  Serial.print(map(input, 0, 512, 0, 180));
  Serial.print("\t\t\t\t\t\t\t");
  setPoint = map(input,0 ,511,-3,3);
  Serial.print("Current Angle : ");
  //Serial.print(map(encoder0Pos, -3, 3, 0, 180));
  Serial.print(encoder0Pos);
  
  Serial.println("\t");
  n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos--;
      //delay(10);
    } else {
      encoder0Pos++;
     // delay(10);
    }
    Serial.print (encoder0Pos);
    Serial.println ();
  }
  encoder0PinALast = n;
  if(setPoint < encoder0Pos)
  {
   digitalWrite(motorPin0, HIGH);
   digitalWrite(motorPin1, LOW);
   delay(10);
  }
  if(setPoint > encoder0Pos)
  {
   digitalWrite(motorPin0, LOW);
   digitalWrite(motorPin1, HIGH);
   delay(10);
  }
  else
  {
   digitalWrite(motorPin0, LOW);
   digitalWrite(motorPin1, LOW);
  }
}
