#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);

int light = 5;
String data;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(light, OUTPUT);
  digitalWrite(light, LOW);
}


void loop()
{
  int i = 0;
  char ch = 0;
  data = "";
  while (mySerial.available())
  {
    delay(5);
    ch = mySerial.read();
    data += ch;
  }
  if (data.length() > 0)
  {
  Serial.println(data);   // data to serial port

  if (data == "turn on light")  //to turn on light
  {
    digitalWrite(light, HIGH);
    Serial.println("light on");
  }

  else if (data == "turn off light") //to turn off light
  {
    digitalWrite(light, LOW);
    Serial.println("light off");
  }
    data="";
  }
}


