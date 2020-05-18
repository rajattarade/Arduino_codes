
void setup() {
   Serial.begin(9600);
   pinMode(4, INPUT);
   pinMode(5, INPUT);
   pinMode(6, INPUT);
   pinMode(7, INPUT);
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);   
}

void loop() {
  
  Serial.print("00");
  Serial.print('\t');
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  Serial.print(digitalRead(4));
  Serial.print('\t');
  Serial.print(digitalRead(5));
  Serial.print('\t');
  Serial.print(digitalRead(6));
  Serial.print('\t');
  Serial.print(digitalRead(7));
  Serial.println();
delay(1000);
  Serial.print("01");
  Serial.print('\t');
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  Serial.print(digitalRead(4));
  Serial.print('\t');
  Serial.print(digitalRead(5));
  Serial.print('\t');
  Serial.print(digitalRead(6));
  Serial.print('\t');
  Serial.print(digitalRead(7));
  Serial.println();
delay(1000);
  Serial.print("10");
  Serial.print('\t');
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  Serial.print(digitalRead(4));
  Serial.print('\t');
  Serial.print(digitalRead(5));
  Serial.print('\t');
  Serial.print(digitalRead(6));
  Serial.print('\t');
  Serial.print(digitalRead(7));
  Serial.println();
delay(1000);
  Serial.print("11");
  Serial.print('\t');
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  Serial.print(digitalRead(4));
  Serial.print('\t');
  Serial.print(digitalRead(5));
  Serial.print('\t');
  Serial.print(digitalRead(6));
  Serial.print('\t');
  Serial.print(digitalRead(7));
  Serial.println();
  
  
  delay(1000);
}
