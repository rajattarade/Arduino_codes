char arra[] = {"+919404292958"};
String strg;
void setup()
{
 Serial.begin(115200); 
} 
void loop()
{
  for(int i=0;i<13;i++)
  strg =  String(strg + arra[i]);

  Serial.print(strg);
  while(1);
}
