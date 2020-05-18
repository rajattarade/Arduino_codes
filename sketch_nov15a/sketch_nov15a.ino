#include <VirtualWire.h>


const int receive_pin = 12;

void setup()
{
    delay(1000);
    Serial.begin(9600);  // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR

    vw_set_rx_pin(receive_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);  // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  int i;

     // Message with a good checksum received, print it.
  Serial.print("Got: ");
  
  for (i = 0; i < buflen; i++)
  {
      Serial.print(buf[i], HEX);
      Serial.print(' ');
  }
  Serial.println();
     }
}

