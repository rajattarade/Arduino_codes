//homeautomation421@gmail.com
//Server_1234

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "DHT.h"


#define FIREBASE_HOST "homeautomation98.firebaseio.com"
#define FIREBASE_AUTH "HqM0CBXmyKQmDRIrfImzA95ZkgfSuv3ADzL7eywU"
#define WIFI_SSID "Manish"
#define WIFI_PASSWORD "oytu8007"                                     //Password of your wifi network 
                                  //Password of your wifi network 
                                   //Password of your wifi network 
DHT dht;

Servo myservo;

#define Relay1 D0 
int val1;

#define Relay2 D1 
int val2;

#define Relay3 D2 
int val3;

#define Relay4 D3 
int val4;

#define LED D5
int valLED=0;

#define PIR D7

int presence = 0;
int temp = 0;
int setTemp = 29;
int automate = 0;
int servoA=0;

void setup() 
{
  Serial.begin(115200);                                                   // Select the same baud rate if you want to see the datas on Serial Monitor
  dht.setup(D6); // data pin 2

  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  pinMode(Relay4,OUTPUT);
  pinMode(LED,OUTPUT);
  
  pinMode(PIR,INPUT);

  digitalWrite(Relay1,HIGH); //All relays turned off
  digitalWrite(Relay2,HIGH);
  digitalWrite(Relay3,HIGH);
  digitalWrite(Relay4,HIGH);

  myservo.attach(D4);

  digitalWrite(LED,valLED);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    valLED=~valLED;
    Serial.print(valLED);
    digitalWrite(LED,valLED);  
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());
  digitalWrite(LED,HIGH);  
  
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  
}

void loop() 
{
  if (Firebase.failed())
      {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      ESP.reset();
      }
      
  val1=Firebase.getString("S1").toInt();
  val2=Firebase.getString("S2").toInt();                                        //Reading the value of the varialble Status from the firebase
  val3=Firebase.getString("S3").toInt();                                        //Reading the value of the varialble Status from the firebase
  val4=Firebase.getString("S4").toInt();
  String TempString = Firebase.getString("SetTemp");
  automate = Firebase.getString("Automate").toInt();
   
  //Reading the value of the varialble Status from the firebase
  servoA=Firebase.getString("Servo").toInt();
  
  temp = dht.getTemperature();
  
  Firebase.setInt("CurrentTemp",temp);
  Serial.print("PIR : ");
  Serial.println(digitalRead(PIR));
  Serial.print("SET TEMP : ");
  Serial.println(TempString);
  String number = TempString.substring(1, 3);
  setTemp = number.toInt();
  Serial.println(setTemp);
  
  
  if(val1==1 && automate==0)                                                             // If, the Status is 1, turn on the Relay1
    {
      digitalWrite(Relay1,LOW); //LOW means Relay On becouse of the optocoupler
      Serial.println("Light 1 ON");
    }
    else if(val1==0 && automate==0)                                                      // If, the Status is 0, turn Off the Relay1
    {                                      
      digitalWrite(Relay1,HIGH); //Relay 1 OFF
      Serial.println("Light 1 OFF");
    }  
  if(automate==1 && digitalRead(PIR))                                                      // If, the Status is 0, turn Off the Relay1
    {                                      
      digitalWrite(Relay1,LOW); //Relay 1 OFF
      Serial.println("Light 1 ON Automated");
    }
  else if(automate==1 && !digitalRead(PIR))                                                      // If, the Status is 0, turn Off the Relay1
    {                                      
      digitalWrite(Relay1,HIGH); //Relay 1 OFF
      Serial.println("Light 1 OFF Automated");
    }
    
    
  if(val2==1 && automate==0)                                                             // If, the Status is 1, turn on the Relay2
     {
      digitalWrite(Relay2,LOW);
      Serial.println("FAN 1 ON");
    }
  else if(val2==0 && automate==0)                                                      // If, the Status is 0, turn Off the Relay2
    {                                      
      digitalWrite(Relay2,HIGH);
      Serial.println("FAN 1 OFF");
    }
      
  if(automate==1 && (temp > setTemp))
  {
   digitalWrite(Relay2,LOW);
   Serial.println("FAN 1 ON AUTOMATED");
  }
  
  if(automate==1 && (temp <= setTemp))
  {
   digitalWrite(Relay2,HIGH);
   Serial.println("FAN 1 OFF AUTOMATED");
  }
  
  
  if(val3==1)                                                             // If, the Status is 1, turn on the Relay3
     {
      digitalWrite(Relay3,LOW);
      Serial.println("light 3 ON");
    }
    else if(val3==0)                                                      // If, the Status is 0, turn Off the Relay3
    {                                      
      digitalWrite(Relay3,HIGH);
      Serial.println("light 3 OFF");
    }
  if(val4==1)                                                             // If, the Status is 1, turn on the Relay4
     {
      digitalWrite(Relay4,LOW);
      Serial.println("light 4 ON");
    }
    else if(val4==0)                                                      // If, the Status is 0, turn Off the Relay4
    {                                      
      digitalWrite(Relay4,HIGH);
      Serial.println("light 4 OFF");
    }
    
  myservo.write(servoA);
  Serial.print("Servo Angle : ");
  Serial.println(servoA); 
}
