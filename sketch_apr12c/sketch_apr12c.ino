int led = 5;
void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);

}

void loop() {
int sensr = analogRead (A0);
sensr = map (sensr, 0, 1023, 0, 255);
analogWrite (led, sensr);


 
   // put your main code here, to run repeatedly:

}
