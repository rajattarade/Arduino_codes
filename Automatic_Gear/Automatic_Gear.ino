#define clutch 5
#define ShiftF 6
#define ShiftB 7
#define pump 8

int currentGear = 0;


void setup() {
  pinMode(clutch, OUTPUT);
  pinMode(ShiftF, OUTPUT);
  pinMode(ShiftB, OUTPUT);
  pinMode(pump, OUTPUT);
  
digitalWrite(clutch, HIGH);
digitalWrite(ShiftF, HIGH);
digitalWrite(ShiftB, HIGH);
digitalWrite(pump, HIGH);

currentGear = 0;
}

void loop() {
//digitalWrite(pump, LOW);
//delay(500);
//digitalWrite(clutch, LOW);
//
//PushF();
//
//digitalWrite(clutch, HIGH);
//delay(500);
//digitalWrite(pump, HIGH);
//
//
//delay(2000);
//
digitalWrite(pump, LOW);
delay(500);
digitalWrite(clutch, LOW);
delay(2000);

digitalWrite(clutch, HIGH);
delay(500);
digitalWrite(pump, HIGH);


while(1);
}

void PushF()
{
  
 delay(1000);
 digitalWrite(ShiftF, LOW);
 delay(500);
 digitalWrite(ShiftF, HIGH);
 delay(500);
}

void PushB()
{
 delay(1000);
 digitalWrite(ShiftB, LOW);
 delay(500);
 digitalWrite(ShiftB, HIGH);
  delay(500);
}
