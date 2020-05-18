#define out 5
 int i=0;
 
void setup() {

  pinMode(3, OUTPUT);
}

void loop() {

 for(i=0;i<255;i++)
 {
 analogWrite(out, i);
 delay(5);
 }
 
 for(i=250;i>0;i--)
 {
 analogWrite(out, i);
 delay(5);
 }
 
}
