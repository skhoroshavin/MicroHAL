
#pragma once

#include <avr/io.h>
#include <ports/avr/timer_utils.h>

#define avr_basic_timer_counter()          (TCNT0)
#define avr_basic_timer_set_counter(VALUE) do { TCNT0 = (VALUE) } while(0)

#define avr_basic_timer_has_overflow()   (TIFR0 & (1 << TOV0))
#define avr_basic_timer_clear_overflow() do { TIFR0 |= (1 << TOV0); } while(0)

typedef struct
{
	avr_timer_clock_t clock;
	avr_timer_mode_t  mode;
	avr_timer_pwm_t   pwm_a;
	avr_timer_pwm_t   pwm_b;
} avr_basic_timer_config_t;

void avr_basic_timer_setup( const avr_basic_timer_config_t * config );
