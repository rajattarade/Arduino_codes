#include <Keypad.h>
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include<EEPROM.h>


char password[4];
char pass[4], pass1[4];

RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network

const uint16_t door1 = 02;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t master = 00;

int i = 0;
char customKey = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {7, 8, A5, A4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A3, A2, A1, A0}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int ledG = 6;
int alertS = 0;
void setup()
{
  SPI.begin();
  radio.begin();
  network.begin(90, door1);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MAX);
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(ledG, OUTPUT);
  digitalWrite(ledG, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  Serial.print(" Electronic ");
  Serial.print(" Keypad Lock ");
  delay(200);
  Serial.println("Enter Ur Passkey:");
  for (int j = 0; j < 4; j++)
  {
    pass[j] = EEPROM.read(j);
    Serial.print(pass[j]);
  }

}

void loop()
{
back:
  network.update();
  RF24NetworkHeader header(master);
  int alertType = 0;
  if (analogRead(A7) < 100)
    unlock();
  customKey = customKeypad.getKey();
  if (customKey == '#')
  {
alert:
    Serial.println("SMS SIREN !!");
    alertType = 2;
    bool ok = network.write(header, &alertType, sizeof(alertType));
    delay(100);
    goto back;
  }
  if (customKey == '*')
  {
    change();
    if (alertS == 1)
    {
      digitalWrite(ledG, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      goto alert;
    }
  }
  if (customKey)
  {
    password[i++] = customKey;
    Serial.print(customKey);

    if (i == 1)
      digitalWrite(led1, HIGH);
    if (i == 2)
      digitalWrite(led2, HIGH);
    if (i == 3)
      digitalWrite(led3, HIGH);
    if (i == 4)
      digitalWrite(led4, HIGH);
  }
  if (i == 4)
  {
    delay(200);
    if (!(strncmp(password, pass, 4)))
    {
      unlock();
    }
    else
    {
      Serial.println("SMS sent");
      alertType = 1;
      bool ok = network.write(header, &alertType, sizeof(alertType));
      delay(500);
      i = 0;
      digitalWrite(ledG, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }
  }
}

void unlock()
{
  digitalWrite(ledG, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  Serial.println("Passkey Accepted");
  delay(20000);
  i = 0;
  digitalWrite(ledG, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}

void change()
{
  alertS = 0;
  int j = 0;
  Serial.println("UR Current Passk");
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  while (j < 4)
  {
    char key = customKeypad.getKey();
    if (key == '#')
    {
      alertS = 1;
      goto backtomain;
    }
    if (key)
    {
      pass1[j++] = key;
      Serial.print(key);
      if (j == 1)
        digitalWrite(led1, LOW);
      if (j == 2)
        digitalWrite(led2, LOW);
      if (j == 3)
        digitalWrite(led3, LOW);
      if (j == 4)
        digitalWrite(led4, LOW);
    }
    key = 0;
  }
  delay(500);

  if ((strncmp(pass1, pass, 4)))
  {
    Serial.println("Wrong Passkey...");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
  else
  {
    j = 0;
    Serial.println("Enter New Passk:");
    digitalWrite(ledG, HIGH);
    while (j < 4)
    {
      char key = customKeypad.getKey();
      if (key == '#')
      {
        alertS = 1;
        goto backtomain;
      }
      if (key)
      {
        pass[j] = key;
        Serial.print(key);
        if (j == 0)
          digitalWrite(led1, HIGH);
        if (j == 1)
          digitalWrite(led2, HIGH);
        if (j == 2)
          digitalWrite(led3, HIGH);
        if (j == 3)
          digitalWrite(led4, HIGH);
        EEPROM.write(j, key);
        j++;
      }
    }
    Serial.println(" Done......");
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(ledG, LOW);
    delay(500);
    digitalWrite(ledG, HIGH);
    delay(500);
    digitalWrite(ledG, LOW);
    delay(100);
  }
backtomain:
  customKey = 0;
}
