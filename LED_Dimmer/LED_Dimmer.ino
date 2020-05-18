int led = 9;    
int sen=2;
int val=0;
boolean state=0;

void setup() 
{
  pinMode(sen,INPUT);
  //pinMode(led,OUTPUT);
  
  digitalWrite(sen,LOW);
  //digitalWrite(led,LOW);
  Serial.begin(9600);
}

void loop() 
{
 back:
 if(digitalRead(sen)==LOW)
 goto back;
 while(digitalRead(sen)==HIGH)
 {
  if(state)
  {
  val--;
  if(val<0)
  val=0;
  Serial.println(val);
  delay(2);
  analogWrite(led,val);
  }
  else
  {
  val++;
  if(val>255)
  val=255;
  Serial.println(val);
  delay(10);
  analogWrite(led,val);
  }
 }
 state=!state;
}
