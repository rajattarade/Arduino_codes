#define EN        8  

//Direction pin

#define Y_DIR     13
#define Z_DIR     5

//Step pin

#define Y_STP     12
#define Z_STP     2 



int delayTime=800; //Delay between each pause (uS)
int stps=200;// Steps to move


void step(boolean dir, byte dirPin, byte stepperPin, int steps)

{

  digitalWrite(dirPin, dir);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(delayTime); 
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(delayTime); 
  }
}

void setup(){

 
  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);

}

void loop(){

  step(false, Z_DIR, Z_STP, stps); //X, Clockwise
  step(false, Y_DIR, Y_STP, stps); //Y, Clockwise
  step(true, Z_DIR, Z_STP, stps); //X, Counterclockwise
  step(true, Y_DIR, Y_STP, stps); //Y, Counterclockwise
  
for (int i = 0; i < 200; i++) {
  step(false, Z_DIR, Z_STP, 1); //X, Clockwise
  step(false, Y_DIR, Y_STP, 1); //Y, Clockwise
}
  for (int i = 0; i < 200; i++) {
  step(true, Z_DIR, Z_STP, 1); //X, Counterclockwise
  step(true, Y_DIR, Y_STP, 1); //Y, Counterclockwise
  }
  
  
}
