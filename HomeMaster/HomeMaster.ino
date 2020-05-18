#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 7);

RF24 radio(9, 10);               // nRF24L01 (CE,CSN)

RF24Network network(radio);      // Include the radio in the network

const uint16_t master = 00;   // Address of this node in Octal format ( 04,031, etc)
#define siren 2
#define sirenRelay 3


void setup() {
  SPI.begin();
  radio.begin();
  mySerial.begin(9600);   // Setting the baud rate of GSM Module
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  network.begin(90, master);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MAX);
  pinMode(siren, OUTPUT);
  pinMode(sirenRelay, OUTPUT);
  digitalWrite(sirenRelay, HIGH);
}
void loop() {
  network.update();
  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    int incomingData;
    network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
    Serial.println(header.from_node);
    Serial.println(incomingData);
    
    if (header.from_node == 1)
    {
      if(incomingData==1)
      {
        digitalWrite(siren, HIGH);
        Serial.println("Door 1 : 1");
        for(int q=0 ; q<8 ; q++)
        {
        mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
        delay(500);  // Delay of 1000 milli seconds or 1 second
        mySerial.println("AT+CMGS=\"+919763486122\"\r"); // Replace x with mobile number
        delay(500);
        mySerial.println("Wrong Password at Door 1");// The SMS text you want to send
        delay(100);
        mySerial.println((char)26);// ASCII code of CTRL+Z
        delay(500);
         }
        digitalWrite(siren, LOW);
      }
      
      if(incomingData==2)
      {
        digitalWrite(siren, HIGH);
        digitalWrite(sirenRelay, LOW);
        Serial.println("Door 1 : 2");
        for(int q=0 ; q<8 ; q++)
        {
        mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
        delay(500);  // Delay of 1000 milli seconds or 1 second
        mySerial.println("AT+CMGS=\"+919763486122\"\r"); // Replace x with mobile number
        delay(500);
        mySerial.println("Door 1 Triggered");// The SMS text you want to send
        delay(100);
        mySerial.println((char)26);// ASCII code of CTRL+Z
        delay(500);
        }
        digitalWrite(siren, LOW);
        digitalWrite(sirenRelay, HIGH);     
      }
    }
    if (header.from_node == 2)
    {
       if(incomingData==1)
      {
        digitalWrite(siren, HIGH);
        Serial.println("Door 2 : 1");
        mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
        delay(500);  // Delay of 1000 milli seconds or 1 second
        mySerial.println("AT+CMGS=\"+919763486122\"\r"); // Replace x with mobile number
        delay(500);
        mySerial.println("Wrong Password at Door 2");// The SMS text you want to send
        delay(100);
        mySerial.println((char)26);// ASCII code of CTRL+Z
        delay(1000);
        digitalWrite(siren, LOW);
      }
      
      if(incomingData==2)
      {
        digitalWrite(siren, HIGH);
        digitalWrite(sirenRelay, LOW);
        Serial.println("Door 2 : 2");
        mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
        delay(500);  // Delay of 1000 milli seconds or 1 second
        mySerial.println("AT+CMGS=\"+919763486122\"\r"); // Replace x with mobile number
        delay(500);
        mySerial.println("Door 2 Triggered");// The SMS text you want to send
        delay(100);
        mySerial.println((char)26);// ASCII code of CTRL+Z
        delay(1000);
        digitalWrite(siren, LOW);
        delay(4000);
        digitalWrite(sirenRelay, HIGH);     
      }
    }
     if (header.from_node == 3)
    {
       if(incomingData==1)
      {
        digitalWrite(siren, HIGH);
        Serial.println("Door 3 : 1");
        mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
        delay(500);  // Delay of 1000 milli seconds or 1 second
        mySerial.println("AT+CMGS=\"+919763486122\"\r"); // Replace x with mobile number
        delay(500);
        mySerial.println("Wrong Password at Door 3");// The SMS text you want to send
        delay(100);
        mySerial.println((char)26);// ASCII code of CTRL+Z
        delay(1000);
        digitalWrite(siren, LOW);
        
      }
      
      if(incomingData==2)
      {
        digitalWrite(siren, HIGH);
        digitalWrite(sirenRelay, LOW);
        Serial.println("Door 3 : 2");
        mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
        delay(500);  // Delay of 1000 milli seconds or 1 second
        mySerial.println("AT+CMGS=\"+919763486122\"\r"); // Replace x with mobile number
        delay(500);
        mySerial.println("Door 3 Triggered");// The SMS text you want to send
        delay(100);
        mySerial.println((char)26);// ASCII code of CTRL+Z
        delay(1000);
        digitalWrite(siren, LOW);
        delay(4000);
        digitalWrite(sirenRelay, HIGH);     
      }
    }
  }
}




