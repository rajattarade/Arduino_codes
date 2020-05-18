int pin=9;
void setup() {
  // put your setup code here, to run once:
 pinMode(pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(pin, HIGH);
 delay(5000);
 digitalWrite(pin, LOW);
 delay(5000);
 digitalWrite(pin, HIGH);
 delay(5000);
 while(1);
}
