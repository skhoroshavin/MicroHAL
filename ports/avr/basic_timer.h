
#pragma once

#include <avr/io.h>

inline uint8_t avr_basic_timer_counter() { return TCNT0; }
inline void    avr_basic_timer_set_counter( uint8_t value ) { TCNT0 = value; }

inline uint8_t avr_basic_timer_overflow() { return TIFR0 & (1 << TOV0); }
inline void    avr_basic_timer_clear_overflow() { TIFR0 |= (1 << TOV0); }

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
