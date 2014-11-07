
#pragma once

#include <avr/io.h>
#include <core/timer.h>

#define avr_basic_timer_counter()          (TCNT0)
#define avr_basic_timer_set_counter(VALUE) do { TCNT0 = (VALUE) } while(0)

#define avr_basic_timer_has_overflow()   (TIFR0 & (1 << TOV0))
#define avr_basic_timer_clear_overflow() do { TIFR0 |= (1 << TOV0); } while(0)

typedef enum
{
	AVR_BASIC_TIMER_OFF      = 0,
	AVR_BASIC_TIMER_CLK      = 1,
	AVR_BASIC_TIMER_CLK_8    = 2,
	AVR_BASIC_TIMER_CLK_64   = 3,
	AVR_BASIC_TIMER_CLK_256  = 4,
	AVR_BASIC_TIMER_CLK_1024 = 5
} avr_basic_timer_mode_t;

void avr_basic_timer_init( avr_basic_timer_mode_t mode );
