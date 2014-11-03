
#include <ports/avr/basic_timer.h>

void avr_basic_timer_init( avr_basic_timer_mode_t mode )
{
	TCCR0B = mode;
}
