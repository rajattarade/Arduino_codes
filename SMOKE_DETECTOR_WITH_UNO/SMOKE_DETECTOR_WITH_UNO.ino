#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800
SoftwareSerial mySerial(11, 12); //SIM800L Tx & Rx is connected to Arduino #11 & #12

int redLed = 5;
int greenLed = 6;
int buzzer = 7;
int startup = 15;
int smokeA0 = A5;
// Your threshold value
int sensorThres = 400;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.println("AT");
  updateSerial();

  startup = 15;
}

void loop() {
  int analogSensor = analogRead(smokeA0);
  while (startup > 0)
  {
    delay(1000);
    Serial.println(startup--);
  }
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzer, HIGH);
    for (int i = 0; i < 2; i++)
    {
      mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
      updateSerial();
      mySerial.println("AT+CMGS=\"+919404292958\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
      updateSerial();
      mySerial.print("GAS DETECTED !!"); //text content
      updateSerial();
      mySerial.write(26);
      delay(1000);
    }  
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzer, LOW);
  }
  delay(100);
}

void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

