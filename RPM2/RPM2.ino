const int hallSensorPin = 2;                      // connect the hall effect sensor on pin 2
const unsigned long sampleTime = 1000;
const int maxRPM = 1260;                  // maximum RPM for LCD Bar
int rpmMaximum = 0;
int cgear = 0;
int mgear = 0;
#define clutch 5
#define ShiftF 6
#define ShiftB 7
#define pump 8
#define LED1 9
#define LED2 10
#define LED3 11
#define LED4 12
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 3; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)


void setup() 
{
  pinMode(hallSensorPin,INPUT);
  pinMode(clutch, OUTPUT);
  pinMode(ShiftF, OUTPUT);
  pinMode(ShiftB, OUTPUT);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
 
  pinMode(pump, OUTPUT);
  
digitalWrite(clutch, HIGH);
digitalWrite(ShiftF, HIGH);
digitalWrite(ShiftB, HIGH);
digitalWrite(pump, HIGH);
  Serial.begin(9600);
}

void loop() 
{
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 60, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  int rpm = getRPM();
  if (rpm > rpmMaximum) rpmMaximum = rpm;
  Serial.print("RPM = ");
  Serial.print(rpm);
  Serial.print("  MAX RPM = ");
  Serial.print(rpmMaximum);
  mgear=map(rpm,600,1900,1,4);
  if(rpm<600)
  mgear=1;
  if(mgear>4)
  mgear=4;
  int i = mgear - cgear;
  if(i<0)
  {
    Serial.print("  Shift DOWN  ");
    PushB();
    cgear=cgear-1;  
  }

  if(i>0)
  {
     Serial.print("  Shift UP  ");
     PushF();
     cgear=cgear+1;
  }
  Serial.print(" C Gear = ");
  Serial.print(cgear);
  Serial.print(" M Gear = ");
  Serial.println(mgear); 
  switch (cgear)
  {
  case 1:
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    break;
  case 2:
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    break;
  case 3:
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    break;
  case 4:
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    break;
    
  default:
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    break;
  }
}
 
int getRPM()
{
  int count = 0;
  boolean countFlag = LOW;
  unsigned long currentTime = 0;
  unsigned long startTime = millis();
  while (currentTime <= sampleTime)
  {
    if (digitalRead(hallSensorPin) == HIGH)
    {
      countFlag = HIGH;
    }
    if (digitalRead(hallSensorPin) == LOW && countFlag == HIGH)
    {
      count++;
      countFlag=LOW;
    }
    currentTime = millis() - startTime;
  }
  int countRpm = int(60000/float(sampleTime))*count;
  return countRpm;
}


void PushF()
{
 digitalWrite(pump, LOW);
delay(500);
digitalWrite(clutch, LOW); 
 delay(1000);
 digitalWrite(ShiftF, LOW);
 delay(500);
 digitalWrite(ShiftF, HIGH);
 delay(500);
 digitalWrite(clutch, HIGH);
delay(500);
digitalWrite(pump, HIGH);
}

void PushB()
{
  digitalWrite(pump, LOW);
delay(500);
digitalWrite(clutch, LOW);
 delay(1000);
 digitalWrite(ShiftB, LOW);
 delay(500);
 digitalWrite(ShiftB, HIGH);
  delay(500);
  digitalWrite(clutch, HIGH);
delay(500);
digitalWrite(pump, HIGH);
}


