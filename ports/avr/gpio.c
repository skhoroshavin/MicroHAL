
#include <ports/avr/gpio.h>

void avr_gpio_setup( volatile uint8_t * portReg, volatile uint8_t * ddrReg,
					 avr_gpio_mode_t mode, uint8_t start, uint8_t count)
{
	uint8_t mask = 0;
	uint8_t pin, bit;

	for( pin = 0, bit = (1 << start);
		 pin < count;
		 ++pin, bit <<= 1 )
	{
		mask |= bit;
	}

	if( mode & _AVR_HIGH )
		*portReg |= mask;
	else
		*portReg &= ~mask;

	if( mode & _AVR_OUTPUT)
		*ddrReg |= mask;
	else
		*ddrReg &= ~mask;
}
