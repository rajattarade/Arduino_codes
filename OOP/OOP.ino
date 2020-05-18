#include "Instance.h"
#include <Adafruit_NeoPixel.h>

#define PIN        11 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS  72 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Instance P[] = {
                Instance("Sine", 0, 0, 1, 1, "Static", 0, 10, 1, 1),
                Instance("Static", 0, 72, 1, 1, "Sine", 0, 0, 1, 1),
                Instance("Sine", 180, 0, 1, 1, "Static", 0, 10, 1, 1),
                };

String cmdP1;
String cmdP2;
String cmdP3;
String cmdP4;
int startTime = 0;
int currentTime = 0;
int duration = 4;
int x = 0;
int R[]={50,0,0},
    G[]={0,50,0},
    B[]={0,0,50};
int Y[] = {0,
           0,
           0};
int W[] = {0,
           0,
           0};
String cmd;
char d;

boolean cc=false;

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(60);
  startTime = millis();
}

void loop() {
if ( (currentTime - startTime) > duration)
{
  x += 1;
  if (x > 360)
  {
    x = 0;
  }
  startTime = currentTime;
}

  if (Serial.available())
  {
    d = Serial.read();
    if(d=='!')
    cc=true;
    else
    cmd += d; 
  }

currentTime = millis();

if (cc)
{
cmdP1 = GetStringPartAtSpecificIndex(cmd, ',', 0);
cmdP2 = GetStringPartAtSpecificIndex(cmd, ',', 1);
cmdP3 = GetStringPartAtSpecificIndex(cmd, ',', 2);
cmdP4 = GetStringPartAtSpecificIndex(cmd, ',', 3);
int n = cmdP2.toInt()-1;
if(cmdP1=="Y")
{
  if(cmdP3=="Type")
  P[n].setTypeY(cmdP4);
  if(cmdP3=="Xoffset")
  P[n].setXoffsetY(cmdP4.toInt());
  if(cmdP3=="Yoffset")
  P[n].setYoffsetY(cmdP4.toInt());
  if(cmdP3=="Scale")
  P[n].setScaleY(float(cmdP4.toInt())/1000);
  if(cmdP3=="Speed")
  P[n].setSpeedY(float(cmdP4.toInt())/1000);
  if(cmdP3=="Duty")
  P[n].setDutyY(float(cmdP4.toInt())/1000); 
}
else if(cmdP1=="W")
{
  if(cmdP3=="Type")
  P[n].setTypeW(cmdP4);
  if(cmdP3=="Xoffset")
  P[n].setXoffsetW(cmdP4.toInt());
  if(cmdP3=="Yoffset")
  P[n].setYoffsetW(cmdP4.toInt());
  if(cmdP3=="Scale")
  P[n].setScaleW(float(cmdP4.toInt())/1000);
  if(cmdP3=="Speed")
  P[n].setSpeedW(float(cmdP4.toInt())/1000);
  if(cmdP3=="Duty")
  P[n].setDutyW(float(cmdP4.toInt())/1000); 
}
else if(cmdP1=="S")
{
 duration=n;
}
else if(cmdP1=="B")
{
 pixels.setBrightness(n);
}
else if(cmdP1=="C1")
{
 R[0]=cmdP2.toInt();
 G[0]=cmdP3.toInt();
 B[0]=cmdP4.toInt();
}
else if(cmdP1=="C2")
{
 R[1]=cmdP2.toInt();
 G[1]=cmdP3.toInt();
 B[1]=cmdP4.toInt();
}
else if(cmdP1=="C3")
{
 R[2]=cmdP2.toInt();
 G[2]=cmdP3.toInt();
 B[2]=cmdP4.toInt();
}
cc=false;
cmd="";
}
for(int i=2;i>=0;i--)
  {
    Y[i] = P[i].getY(x);
    W[i] = P[i].getW(x);
  }

pixels.clear();
for(int i=2;i>=0;i--)
  {
    for(int q = (Y[i]-(W[i]/2)) ; q <= (Y[i]+(W[i]/2)) ; q++)
      {
        pixels.setPixelColor(q, R[i],G[i],B[i]);  
      }
  }
pixels.show();
}

String GetStringPartAtSpecificIndex(String StringToSplit, char SplitChar, int StringPartIndex)
{
  String originallyString = StringToSplit;
  String outString = "";
  for (int i1 = 0; i1 <= StringPartIndex; i1++)
  {
    outString = ""; //if the for loop starts again reset the outString (in this case other part of the String is needed to take out)
    int SplitIndex = StringToSplit.indexOf(SplitChar); //set the SplitIndex with the position of the SplitChar in StringToSplit

    if (SplitIndex == -1) //is true, if no Char is found at the given Index
    {
      //outString += "Error in GetStringPartAtSpecificIndex: No SplitChar found at String '" + originallyString + "' since StringPart '" + (i1-1) + "'"; //just to find Errors
      return outString;
    }
    for (int i2 = 0; i2 < SplitIndex; i2++)
    {
      outString += StringToSplit.charAt(i2); //write the char at Position 0 of StringToSplit to outString
    }
    StringToSplit = StringToSplit.substring(StringToSplit.indexOf(SplitChar) + 1); //change the String to the Substring starting at the position+1 where last SplitChar found
  }
  return outString;
}

