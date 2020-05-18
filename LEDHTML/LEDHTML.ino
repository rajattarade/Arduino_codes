#include <ESP8266WebServer.h>
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac1;
Adafruit_MCP4725 dac2;
//Set Wifi ssid and password
char ssid[] = "D-Link";
char pass[] = "silverfox1234";

ESP8266WebServer server (80);
MDNSResponder mdns;
//This function takes the parameters passed in the URL(the x and y coordinates of the joystick)
//and sets the motor speed based on those parameters. 
void handleJSData(){
  boolean yDir;
  int y = 2000-(server.arg(0).toInt() * 5);
  int x = 1500+(server.arg(1).toInt() * 5);
  if(x<1015)
  x=1015;
  Serial.print(x);
  Serial.print("  ");
  Serial.print(y);
  Serial.println("  ");
  dac1.setVoltage(y, false);
  dac2.setVoltage(x, false);
//  int aSpeed = abs(y);
//  int bSpeed = abs(y);
  //set the direction based on y being negative or positive
  if ( y < 0 ){
    yDir = 0; 
  }
  else { 
    yDir = 1;
  }  
  //adjust to speed of each each motor depending on the x-axis
  //it slows down one motor and speeds up the other proportionately 
  //based on the amount of turning
//  aSpeed = constrain(aSpeed + x/2, 0, 1023);
//  bSpeed = constrain(bSpeed - x/2, 0, 1023);
//  if(yDir)
//  {
//  //dac1.setVoltage(((aSpeed/2)+511)*4, false);
//  //dac2.setVoltage(((bSpeed/2)+511)*4, false);
//  Serial.print((aSpeed/2)+1500);
//  Serial.print("  ");
//  Serial.print((bSpeed/2)+1500);
//  Serial.println("  ");
//  }
//  else
//  {
//  //dac1.setVoltage((511-(aSpeed/2))*4, false);
//  //dac2.setVoltage((511-(bSpeed/2))*4, false);
//  Serial.print(1500-(aSpeed/2));
//  Serial.print("  ");
//  Serial.print(1500-(bSpeed/2));
//  Serial.println("  ");
//  }
  //return an HTTP 200
  server.send(200, "text/plain", "");   
}

void setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
delay(100);
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(100);
  dac1.begin(0x61);
  dac2.begin(0x60);
  dac1.setVoltage(2000, true);
  dac2.setVoltage(1500, true);
  // Debug console
  Serial.begin(115200);
  //initialize SPIFFS to be able to serve up the static HTML files. 
  if (!SPIFFS.begin()){
    Serial.println("SPIFFS Mount failed");
  } 
  else {
    Serial.println("SPIFFS Mount succesfull");
  }

  if(mdns.begin("robot-01", WiFi.localIP()))
    Serial.println("mDNS responder has started");
  //set the static pages on SPIFFS for the html and js
  server.serveStatic("/", SPIFFS, "/joystick.html"); 
  server.serveStatic("/virtualjoystick.js", SPIFFS, "/virtualjoystick.js");
  //call handleJSData function when this URL is accessed by the js in the html file
  server.on("/jsData.html", handleJSData);  
  server.begin();
  MDNS.addService("http","tcp",80);
  
}

void loop()
{
  server.handleClient();  
}
