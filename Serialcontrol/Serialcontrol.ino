const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot


void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.println("READY");
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available())
 {
   char c=Serial.read();
   if(c=='S')
   {
    int j=0;
    while(Serial.read()!='P')
    {
    j+=4;
    if(j==360)
    j=0;
    Serial.println(int((512*(sin(j * (PI / 180))))+512));
    delay(200);
    }
   }
 }
}
