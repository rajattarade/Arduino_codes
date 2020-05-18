//#include <Wire.h>
//#include <Adafruit_PWMServoDriver.h>

//BASE 10 (2400 to 600)
//Shoulder 11 (2400 = 90; 1300 = 0)
//Elbow 12 (2400 = 90; 1500 = 0)
//Wrist Roll 13 (2600 = 180; 400 = 0)
//Wrist Pitch 14 (2400 = 90; 400 = 0)
//Gripper 15 (1800 = open ,600 = close)

class Anatecharm
{
    //Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
    int pitchV = 50;
    int rollV = 50;
    int gripperV = 0;
    int elbowV = 100;
    int shoulderV = 45;
    int baseV = 50;

    public:
    Anatecharm() {
      //pwm.begin();
      //pwm.setPWMFreq(50);
      pitch(50);
      roll(50);
      gripper(0);
      elbow(100);
      shoulder(45);
      base(50);
    }

    void base(int angle)
    {
      int ang = map(angle, 0, 100, 600, 2400);
      //pwm.writeMicroseconds(10, ang);
      delay(5);
    }
    void shoulder(int angle)
    {
      int ang = map(angle, 0, 100, 1300, 2400);
      //pwm.writeMicroseconds(11, ang);
    }
    void elbow(int angle)
    {
      int ang = map(angle, 0, 100, 2400, 1500);
      //pwm.writeMicroseconds(12, ang);
      Serial.println(ang);
    }
    void gripper(int angle)
    {
      int ang = map(angle, 0, 100, 600, 1800);
      //pwm.writeMicroseconds(15, ang);
    }
    void roll(int angle)
    {
      int ang = map(angle, 0, 100, 400, 2600);
      //pwm.writeMicroseconds(13, ang);
    }
    void pitch(int angle)
    {
      int ang = map(angle, 0, 100, 400, 2400);
      //pwm.writeMicroseconds(14, ang);
    }
    
    int Babaduk(int angle)
    {
     return angle*2;  
    }
};

