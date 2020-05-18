#include <VirtualWire.h>

const int led_pin = 11;
const int transmit_pin = 12;

void setup()
{
  vw_set_tx_pin(transmit_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);   // Bits per sec
  Serial.begin(9600);  
}

byte count = 1;

void loop()
{
  char temp = '0';
  if(Serial.available())
  temp = Serial.read();
  Serial.println(temp);
  char msg[1] = {};

  msg[0] = temp;

  msg[1] = count;
  vw_send((uint8_t *)msg, 1);
  vw_wait_tx(); // Wait until the whole message is gone
  count = count + 1;
    
}
