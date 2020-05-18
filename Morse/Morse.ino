#include <avr/io.h>
#include <util/delay.h>

int msg[]={0,0,2,2,2,2,2,0,1,0,0,2,1,1,1,2,0,0,0,1,2,0,2,2,2,2,2,1,0,1,1,2,1,1,1,2,0,0,1,2,2,2,2,2,2,2};
int ditdelay = 15; 
int main(void)
{
  DDRB = 1 << PB0;
//  while(1)
//  {
//    PORTB  = 0 << PB0;
//    _delay_ms(ditdelay);
//    PORTB  = 1 << PB0;
//    _delay_ms(ditdelay);
//  }
//  // PB2 output
//  CLKMSR = 0x00;
//  CLKPSR = 0x00;
//
//  DDRB = 1 << PB0;
  while (1)
  { 
        for(int i=0;i<sizeof(msg);i++)
        {
        if(msg[i]==0)
        dit();
        if(msg[i]==1)
        dah();
        if(msg[i]==2)
        _delay_ms(ditdelay*3);
        }
  }
}

void dah()
{
  PORTB  = 0 << PB0;
  _delay_ms(ditdelay*3);
  PORTB  = 1 << PB0;
  _delay_ms(ditdelay);
}
void dit()
{
  PORTB  = 0 << PB0;
  _delay_ms(ditdelay);
  PORTB  = 1 << PB0;
  _delay_ms(ditdelay);
}
