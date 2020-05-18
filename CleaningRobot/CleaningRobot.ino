#include <SmartElexPs2Shield.h>
SmartElexPs2Shield ps(10, 11);

// the setup function runs once when you press reset or power the board
#define front_motor1 8
#define front_motor2 9
#define rear_motor1 6
#define rear_motor2 7
#define right_motor1 4
#define right_motor2 5
#define left_motor1 2
#define left_motor2 3
#define ud_motor1 A0
#define ud_motor2 A1
#define spindle_motor1 A2
#define spindle_motor2 A3

boolean sState = LOW;

void setup() {
  ps.begin(9600);
  Serial.begin(9600);
  for (int i = 0; i < 5; i++)
  {
    ps.SetController(ps.AnalogMode);
    delay(20);
  }

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(front_motor1, OUTPUT);
  pinMode(front_motor2, OUTPUT);
  pinMode(rear_motor1, OUTPUT);
  pinMode(rear_motor2, OUTPUT);
  pinMode(right_motor1, OUTPUT);
  pinMode(right_motor2, OUTPUT);
  pinMode(left_motor1, OUTPUT);
  pinMode(left_motor2, OUTPUT);
  pinMode(ud_motor1, OUTPUT);
  pinMode(ud_motor2, OUTPUT);
  pinMode(spindle_motor1, OUTPUT);
  pinMode(spindle_motor2, OUTPUT);
  digitalWrite(spindle_motor2, LOW);
}

// the loop function runs over and over again forever
void loop() {
  ps.ReadControllerButtons();
  delay(20);
  int Yaxis = 123;
  int Xaxis = 123;
  int LXaxis = 0;
  int LYaxis = 0;
  boolean Ydir = LOW;
  boolean Xdir = LOW;
  boolean Rdir = LOW;
  int Ypwm = 0;
  int Xpwm = 0;
  int Rpwm = 0;
  Yaxis = ps.RIGHT_Y_AXIS;
  Xaxis = ps.RIGHT_X_AXIS;
  LXaxis = ps.LEFT_X_AXIS;
  LYaxis = ps.LEFT_Y_AXIS;
  boolean Up = ps.UP;
  boolean Down = ps.DOWN;
  boolean tri = ps.TRIANGLE;
  boolean cro = ps.CROSS;

  if (Yaxis < 120)
  {
    Ydir = HIGH;
    Ypwm = map(Yaxis, 123, 1, 100, 255);
  }
  else if (Yaxis > 125)
  {
    Ydir = LOW;
    Ypwm = map(Yaxis, 123, 255, 100, 255);
  }
  else
  {
    Ypwm = 0;
  }

  if (Xaxis < 120)
  {
    Xdir = HIGH;
    Xpwm = map(Xaxis, 123, 1, 100, 255);
  }
  else if (Xaxis > 125)
  {
    Xdir = LOW;
    Xpwm = map(Xaxis, 123, 255, 100, 255);
  }
  else
  {
    Xpwm = 0;
  }

  if (LXaxis < 120)
  {
    Rdir = HIGH;
    Rpwm = map(LXaxis, 123, 1, 100, 255);
  }
  else if (LXaxis > 125)
  {
    Rdir = LOW;
    Rpwm = map(LXaxis, 123, 255, 100, 255);
  }
  else
  {
    Rpwm = 0;
  }

  if(!Up && Down)
  {
    udmotor(HIGH);
  }
  else if(!Down && Up)
  {
    udmotor(LOW);
  }
  else if(Up && Down)
  udmotorStop();

  if(!tri)
  {
    digitalWrite(spindle_motor1, LOW);
  }
  if(!cro)
  {
    digitalWrite(spindle_motor1, HIGH);
  }

  Serial.print(sState); Serial.print(" ");

  Serial.println();
  if (Rpwm == 0)
  {
    rightmotor(!Ydir , Ypwm);
    leftmotor(Ydir , Ypwm);
    frontmotor(!Xdir, Xpwm);
    rearmotor(Xdir, Xpwm);
  }
  else
  {
    rightmotor(!Rdir , Rpwm);
    leftmotor(!Rdir , Rpwm);
    frontmotor(!Rdir, Rpwm);
    rearmotor(!Rdir, Rpwm);
  }

}

void frontmotor(boolean dir , int pwm)
{
  digitalWrite(front_motor1, dir);
  if (!dir)
    analogWrite(front_motor2, pwm);
  else
    analogWrite(front_motor2, 255 - pwm);
}

void udmotor(boolean dir)
{
  digitalWrite(ud_motor1, dir);
  digitalWrite(ud_motor2, !dir);
}
void udmotorStop()
{
  digitalWrite(ud_motor1, LOW);
  digitalWrite(ud_motor2, LOW);
}


void rearmotor(boolean dir , int pwm)
{
  if (dir)
    analogWrite(rear_motor1, pwm);
  else
    analogWrite(rear_motor1, 255 - pwm);
  digitalWrite(rear_motor2, !dir);
}

void rightmotor(boolean dir , int pwm)
{
  digitalWrite(right_motor1, dir);
  if (!dir)
    analogWrite(right_motor2, pwm);
  else
    analogWrite(right_motor2, 255 - pwm);
}

void leftmotor(boolean dir , int pwm)
{
  digitalWrite(left_motor1, !dir);
  if (dir)
    analogWrite(left_motor2, pwm);
  else
    analogWrite(left_motor2, 255 - pwm);
}

void stopmotors()
{
  digitalWrite(left_motor1, LOW);
  digitalWrite(left_motor2, LOW);
  digitalWrite(right_motor1, LOW);
  digitalWrite(right_motor2, LOW);
  digitalWrite(front_motor1, LOW);
  digitalWrite(front_motor2, LOW);
  digitalWrite(rear_motor1, LOW);
  digitalWrite(rear_motor2, LOW);
  digitalWrite(ud_motor1, LOW);
  digitalWrite(ud_motor2, LOW);
}

void spindle(boolean state)
{
  digitalWrite(spindle_motor1, state);
}

