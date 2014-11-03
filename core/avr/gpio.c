
#include <core/avr/gpio.h>

void avr_gpioB_setup( uint8_t maskOut, uint8_t maskState )
{
	PORTB = maskState;
	DDRB  = maskOut;
}
