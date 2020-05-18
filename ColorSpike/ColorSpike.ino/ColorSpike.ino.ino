#include <Adafruit_NeoPixel.h>

#define PIN        11 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 72 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  
void setup() {
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  pixels.setBrightness(10);
  pixels.show();
}

void loop() {
  if (Serial.available()) {
  String cmd = Serial.readString();
  
  Serial.print(cmd);
  
  cmd.trim();
      
  if (cmd == "Clear")
  {
    pixels.clear();
    pixels.show();
  }
  
  else if(cmd.charAt(0)=='L')
  {
    String hue;
    String center;
    String width;

    hue = GetStringPartAtSpecificIndex(cmd, ',', 1);
    center = GetStringPartAtSpecificIndex(cmd, ',', 2);
    width = GetStringPartAtSpecificIndex(cmd, ',', 3);

    unsigned int hueInt = hue.toInt()*182;
    unsigned int centerInt = (center.toInt())/2;
    unsigned int widthInt = (width.toInt())/2;  

    for(int q=(centerInt-(widthInt/2)) ; q <= (centerInt+(widthInt/2)) ; q++)
    pixels.setPixelColor(q, pixels.ColorHSV(hueInt));
    
    pixels.show();
  }
  
  }

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

