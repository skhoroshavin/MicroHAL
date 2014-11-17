
#include "microhal.h"

void halInit()
{
	led_init();
	sys_clock_init();

	avr_uart_init( 9600 );
}
