#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>

// defines pins numbers
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3
Servo myServo;
// defines variables
long duration;
int distance;
const char* ssid ="ESP8266";
const char* password ="123456789";

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(115200); // Starts the serial communication
myServo.attach(14);
for(uint8_t t = 4; t > 0; t--) 
    {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }
      WiFi.mode(WIFI_STA);
      WiFi.disconnect(true);
      WiFi.begin(ssid,password);
      while (WiFi.status() != WL_CONNECTED)
      {
      delay(500);
      Serial.print(".");
      //pinMode(pir,INPUT);
      Serial.println("Connected");
    }
}

void loop() {
//
//for(int i=15;i<=165;i++)
//    {  
//      myServo.write(i);
//      delay(30);
//      distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
//      Serial.print(i); // Sends the current degree into the Serial Port
//      Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
//      Serial.print(distance); // Sends the distance value into the Serial Port
//      Serial.println("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
//     }
//  // Repeats the previous lines from 165 to 15 degrees
//    for(int i=165;i>15;i--)
//    {  
//      myServo.write(i);
//      delay(30);
//      distance = calculateDistance();
//      Serial.print(i);
//      Serial.print(",");
//      Serial.print(distance);
//      Serial.println(".");
//     }
    // wait for WiFi connection
    if((WiFi.status() == WL_CONNECTED)) 
    {
         HTTPClient http;
         distance = calculateDistance();
         Serial.print(distance);
         if(distance<15)
        {
          digitalWrite(0,HIGH);
          Serial.print("[HTTP] begin...\n");
          // requesting required link 
          http.begin("http://192.168.4.1/pir"); //HTTP
          Serial.print("[HTTP] GET...\n");
          // start connection and send HTTP header
          int httpCode = http.GET();
          http.end();
        }      
       }
}

int calculateDistance()
{
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
return distance;  
}
