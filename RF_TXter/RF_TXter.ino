
char sndr[4] = {'0','0','0','0'};
const int led_pin = 13;
const int transmit_pin = 12;
#define pushButton2 2
#define pushButton3 3
#define pushButton4 4
#define pushButton5 5
#define pushButton6 6
#define pushButton7 7
#define pushButton8 8
#define pushButton9 9
#define pushButtonA0 A0
#define pushButtonA4 A4
#define pushButtonA5 A5


void trans();

void setup()
{
  
}

char count = '1';

void loop()
{
 sndr[0]='0';
   if(digitalRead(pushButtonA5))
  sndr[1]='1';
  else
  sndr[1]='0';
  if(digitalRead(pushButtonA4))
  sndr[2]='1';
  else
  sndr[2]='0';
  
 if(digitalRead(pushButtonA0))
 {
  sndr[0]='9';
 }
  if(digitalRead(pushButton9))
 {
  sndr[0]='8';
 }
  if(digitalRead(pushButton7))
 {
  sndr[0]='7';
 }
  if(digitalRead(pushButton8))
 {
  sndr[0]='6';
 }
  if(digitalRead(pushButton6))
 {
  sndr[0]='5';
 }
  if(digitalRead(pushButton5))
 {
  sndr[0]='4';
 }
  if(digitalRead(pushButton3))
 {
  sndr[0]='3';
 }
  if(digitalRead(pushButton2))
 {
  sndr[0]='2';
 }
  if(digitalRead(pushButton4))
 {
  sndr[0]='1';
 }
 trans();
 } 



void trans()
{
  sndr[3]=count;
  vw_send((uint8_t *)sndr, 4);
  vw_wait_tx(); // Wait until the whole message is gone
  count = count + '1';   
  if(count=='9')
  count='1'; 
}
