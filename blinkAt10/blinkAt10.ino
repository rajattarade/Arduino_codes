#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <avr/wdt.h>

// Wake up by WDT interrupt.
// Don't need to do anything here but (auto-) clearing the interrupt flag.
EMPTY_INTERRUPT(WDT_vect)


/*
  Delay in powerdown mode. Wake up by watchdog interrupt.
*/
void delay_power_down_wdt(uint8_t wdto)
{
  wdt_reset();
  wdt_enable(wdto);
  WDTCSR |= (1 << WDIE);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  // Make sure interrups are enabled and the I flag is restored
  NONATOMIC_BLOCK(NONATOMIC_RESTORESTATE)
  {
    sleep_cpu();
    wdt_disable();
  }
  sleep_disable();
}

int main(void)
{
  int i;

  // PB0 and PB1 outputs
  DDRB = (1 << PB0);
  // Timer0 in mode 14, fast PWM with ICR0 as top.
  // Enable OC0A and OC0B, lower mode bits
  TCCR0A = (1 << COM0A1) | (1 << WGM01);
  // Set top to 1000
  ICR0 = 1000;
  // Start timer with prescaler 1:8 and set upper mode bits
  TCCR0B = (1 << CS01)  | (1 << WGM03) | (1 << WGM02);

  sei();

  while (1)
  {
    for (i = 1000; i >= 750; i--)
    {
      OCR0A = i;
      _delay_us(300);
    }
    for (i = 750; i <= 1000; i++)
    {
      OCR0A = i;
      _delay_us(300);
    }

    for (i = 1000; i >= 250; i--)
    {
      OCR0A = i;
      _delay_us(100);
    }
    for (i = 250; i <= 1000; i++)
    {
      OCR0A = i;
      _delay_us(100);
    }
    delay_power_down_wdt(WDTO_8S);
  }
}
