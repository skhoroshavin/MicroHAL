
#pragma once

#include <avr/io.h>

enum
{
	_avr_timer_prescaler_bit_1    = 1,
	_avr_timer_prescaler_bit_8    = 2,
	_avr_timer_prescaler_bit_64   = 3,
	_avr_timer_prescaler_bit_256  = 4,
	_avr_timer_prescaler_bit_1024 = 5
};
#define _AVR_TIMER_PRESCALER_BIT(value) _avr_timer_prescaler_bit_##value

