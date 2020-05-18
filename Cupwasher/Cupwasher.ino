#define S1 2
#define S5 3
#define S4 4
#define soap 5
#define water 6
#define startButton 10

void valveClose(int x)
{
 digitalWrite(x, HIGH);
 delay(2000);  
}
void valveOpen(int x)
{
 digitalWrite(x, LOW);
 delay(2000);  
}

void pumpOn(int x)
{
 digitalWrite(x, LOW); 
}

void pumpOff(int x)
{
 digitalWrite(x, HIGH); 
}

void setup() {
  pinMode(S1, OUTPUT);
  pinMode(S4, OUTPUT);
  pinMode(S5, OUTPUT);
  pinMode(soap, OUTPUT);
  pinMode(water, OUTPUT);
  pinMode(startButton, INPUT_PULLUP);
  digitalWrite(S1, HIGH);
  digitalWrite(S4, HIGH);
  digitalWrite(S5, HIGH);
  digitalWrite(soap, HIGH);
  digitalWrite(water, HIGH);
}

void loop() {
  int i=0;
  while(digitalRead(startButton)==0)
  {
    i++;
    delay(1);
    if(i>150)
    {
      runSystem();
    }
  }
}

//Edit the code below this
//Edit the code below this
//Edit the code below this
//Edit the code below this
//Edit the code below this
//Edit the code below this
//Edit the code below this
//Edit the code below this
//Edit the code below this
//Edit the code below this
//Edit the code below this

void runSystem()
{
   valveOpen(S4);
   pumpOn(soap);
   delay(1000);
   pumpOff(soap);
   delay(1000);
   valveClose(S4);

   valveOpen(S5);
   pumpOn(water);
   delay(5000);
   pumpOff(water);
   delay(1000);
   valveClose(S5);
  
   delay(5000);

   valveOpen(S1);
   pumpOn(water);
   delay(5000);
   pumpOff(water);
   delay(1000);
   valveClose(S1);

}


