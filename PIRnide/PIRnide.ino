int LED = D5;
int PIR_Input = 9;

void setup(){
 pinMode(PIR_Input,INPUT);
 pinMode(LED,OUTPUT);
 Serial.begin(9600);
 Serial.println("NEW COde"); 
}

void loop() {
 digitalWrite(LED, digitalRead(PIR_Input));
 delay(10);
 Serial.println(digitalRead(PIR_Input));
}
