#define EN        8  

//Direction pin
#define X_DIR     5 
#define Y_DIR     6
#define Z_DIR     7

//Step pin
#define X_STP     2
#define Y_STP     3 
#define Z_STP     4 



int delayTime=400; //Delay between each pause (uS)
int stps=800;// Steps to move


// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro;

int16_t ax, ay, az;
#define range 10

int y[range]={0};
int x[range]={0};
void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);

  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, HIGH);

}

void loop() {
      accelgyro.getAcceleration(&ax, &ay, &az);

int avgx=0;
x[range-1]=ax;
for (int i=0;i<range;i++)
{
          x[i]=x[i+1];
}
for (int i=0;i<range;i++)
{
          avgx=avgx+x[i];
}
avgx=avgx/range;

int avgy=0;
y[range-1]=ay;
for (int i=0;i<range;i++)
{
          y[i]=y[i+1];
}
for (int i=0;i<range;i++)
{
          avgy=avgy+y[i];
}
avgy=avgy/range;

/*if x > 500 X motor CounterClock*/
if(avgx>600)
{
step(true, X_DIR, X_STP, 1);
delay(20);
}
if(avgx<400)
{
step(false, X_DIR, X_STP, 1);
delay(20);
}
          Serial.print("Avg x\t");
          Serial.print(avgx);
          Serial.print("\t");
          Serial.print("Avg y\t");
          Serial.println(avgy);
          delay(10);
}



void step(boolean dir, byte dirPin, byte stepperPin, int steps)

{
  digitalWrite(EN, LOW);
  digitalWrite(dirPin, dir);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(delayTime); 
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(delayTime); 
  }

}
