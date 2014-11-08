
#include <ports/avr/basic_timer.h>

void avr_basic_timer_setup( const avr_basic_timer_config_t * config )
{
	TCCR0A = (config->pwm_a << 6) | (config->pwm_b << 4) | config->mode;
	TCCR0B = config->clock;
}
