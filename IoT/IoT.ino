#include <ESP8266WiFi.h>
 
const char* ssid = "D-Link";
const char* password = "silverfox123";
int sensor0Th = 0;
char sensor0Type = '\0';
int sensor0Value=0;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  // prepare GPIO2
  pinMode(D2, OUTPUT);
  pinMode(A0, INPUT);
  
  digitalWrite(D2, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.println(WiFi.localIP());
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
//  if (!client) {
//    return;
//  }
  
  // Wait until the client sends some data
 // Serial.println("new client");
//  while(!client.available()){
//    delay(1);
//  }
  
  // Read the first line of the request
  String req = "0";
  if(client)
  {
  req = client.readStringUntil('\r');
  sensor0Th = (req.substring(8,11)).toInt();
  sensor0Type = req[7];
  client.flush();
  }
  Serial.println(req);
  Serial.println(sensor0Th);
  Serial.println(sensor0Type);
 
  delay(1);
 // Serial.println("Client disonnected");
 
  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
  
sensor0Value = analogRead(A0);
Serial.println(sensor0Value);
if(sensor0Type == '1')
  {
   if(sensor0Value < sensor0Th)
   digitalWrite(D2, HIGH);
   else
   digitalWrite(D2, LOW);
  }
  if(sensor0Type == '2')
  {
   if(sensor0Value > sensor0Th)
   digitalWrite(D2, HIGH);
   else
   digitalWrite(D2, LOW);
  }
  if(sensor0Type == '3')
  {
   if(sensor0Value == sensor0Th)
   digitalWrite(D2, HIGH);
   else
   digitalWrite(D2, LOW);
  }
}
