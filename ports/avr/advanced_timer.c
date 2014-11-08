
#include "advanced_timer.h"

void avr_advanced_timer_setup( const avr_advanced_timer_config_t * config )
{
	TCCR1A = (config->pwm_a << 6) | (config->pwm_b << 4) | (config->mode & 0x3);
	TCCR1B = ((config->mode >> 2) << 3) | config->clock;
}
