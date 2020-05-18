#include <VirtualWire.h>
#include <ServoTimer.h>

ServoTimer2 myservo;
const int receive_pin = 12;
char temp = '0';
int cv = '3';
char pv = '0';

#define L1_MOTOR 5
#define L2_MOTOR 4

#define R1_MOTOR 2
#define R2_MOTOR 3

#define UD1_MOTOR 6
#define UD2_MOTOR 7

#define LR1_MOTOR 8
#define LR2_MOTOR 9

#define LED A4
#define IRLED A5

void setup() {
  Serial.begin(9600);
  pinMode(L1_MOTOR, OUTPUT);
  pinMode(L2_MOTOR, OUTPUT);
  pinMode(R1_MOTOR, OUTPUT);
  pinMode(R2_MOTOR, OUTPUT);
  pinMode(LR1_MOTOR, OUTPUT);
  pinMode(LR2_MOTOR, OUTPUT);
  pinMode(UD1_MOTOR, OUTPUT);
  pinMode(UD2_MOTOR, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(IRLED, OUTPUT);
  
  Serial.println("READY");
  myservo.attach(10);
  myservo.write(1500); 
  delay(500);
    // Initialise the IO and ISR

    vw_set_rx_pin(receive_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);  // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
 }

void loop()
{
    halt();
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
      {
       temp = buf[0];
       Serial.println(buf[1]);
       Serial.println(buf[2]);
    switch(temp)
    {
    case '0':
    halt();
    break;
    case '1':
    Serial.println("1");
    forward();
    delay(200);
    break;
    case '2':
    Serial.println("2");
    reverse();
    delay(200);
    break;
    case '3':
    Serial.println("3");
    turnLeft();
    delay(200);
    break;
    case '4':
    Serial.println("4");
    turnRight();
    delay(200);
    break;
    case '5':
    Serial.println("5");
    gunLeft();
    delay(200);
    break;
    case '6':
    Serial.println("6");
    gunRight();
    delay(200);
    break;
    case '7':
    Serial.println("7");
    gunUp();
    delay(200);
    break;
    case '8':
    Serial.println("8");
    gunDown();
    delay(200);
    break;
    case '9':
    fire();
    delay(200);
    break;
    default:
    Serial.println("ERROR");
    }
      }
    /*while(cv==pv)
    {
      halt();
      Serial.println("EEEEE");
    }
    pv = cv; */
 
delay(50);
}

void halt()
{
   digitalWrite(L1_MOTOR, LOW);
   digitalWrite(L2_MOTOR, LOW);
   digitalWrite(R1_MOTOR, LOW);
   digitalWrite(R2_MOTOR, LOW);
   digitalWrite(LR1_MOTOR, LOW);
   digitalWrite(LR2_MOTOR, LOW);
   digitalWrite(UD1_MOTOR, LOW);
   digitalWrite(UD2_MOTOR, LOW);
   myservo.write(1500);
}

void forward()
{
   digitalWrite(L1_MOTOR, HIGH);
   digitalWrite(L2_MOTOR, LOW);
   digitalWrite(R1_MOTOR, HIGH);
   digitalWrite(R2_MOTOR, LOW);
}

void reverse()
{
   digitalWrite(L1_MOTOR, LOW);
   digitalWrite(L2_MOTOR, HIGH);
   digitalWrite(R1_MOTOR, LOW);
   digitalWrite(R2_MOTOR, HIGH);
}

void turnLeft()
{
   digitalWrite(L1_MOTOR, LOW);
   digitalWrite(L2_MOTOR, HIGH);
   digitalWrite(R1_MOTOR, HIGH);
   digitalWrite(R2_MOTOR, LOW);
}

void turnRight()
{
   digitalWrite(L1_MOTOR, HIGH);
   digitalWrite(L2_MOTOR, LOW);
   digitalWrite(R1_MOTOR, LOW);
   digitalWrite(R2_MOTOR, HIGH);
}

void gunLeft()
{
   digitalWrite(LR1_MOTOR, LOW);
   digitalWrite(LR2_MOTOR, HIGH);
}

void gunRight()
{
   digitalWrite(LR1_MOTOR, HIGH);
   digitalWrite(LR2_MOTOR, LOW);
}

void gunUp()
{
   digitalWrite(UD1_MOTOR, HIGH);
   digitalWrite(UD2_MOTOR, LOW);
}

void gunDown()
{
   digitalWrite(UD1_MOTOR, LOW);
   digitalWrite(UD2_MOTOR, HIGH);
}

void fire()
{  Serial.println("FIRE");
   myservo.write(1000);
   delay(500);
   myservo.write(1500);  
}




