//
//    FILE: StringSplit.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo
//    DATE: 2016-01-24
//     URL: http://forum.arduino.cc/index.php?topic=374234
//
// Released to the public domain
//

uint32_t start;
uint32_t stop;

String TestString = "L!013!12!1!";
String StringSplits[4];

void setup()
{
  Serial.begin(9600);
  Serial.print("String to split: ");
  Serial.println(TestString);

  delay(1000);
  for (int i = 0; i < 4; i++)
  {
    StringSplits[i] = GetStringPartAtSpecificIndex(TestString, '!', i);
    Serial.print("\tPart ");
    Serial.print(i);
    Serial.print("\t:");
    Serial.println(StringSplits[i]); //see it on serial monitor
  }
  Serial.println("Done 1!");
}

void loop()
{
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


String GetStringPartAtSpecificIndex2(String StringToSplit, char SplitChar, int StringPartIndex)
{
  int cnt = 0;
  int pos = 0;
  for (int il = 0; il < StringToSplit.length(); il++)
  {
    if (cnt == StringPartIndex)
    {
      int bpos = pos;
      while (pos < StringToSplit.length() && StringToSplit[pos] != SplitChar) pos++;
      return StringToSplit.substring(bpos, pos);
    }
    if (StringToSplit[il] == SplitChar)
    {
      pos = il + 1;
      cnt++;
    }
  }
  return "";
}
