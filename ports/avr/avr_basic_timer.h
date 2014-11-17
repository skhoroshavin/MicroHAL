
#pragma once

#include <ports/avr/_avr_timer_utils.h>

#define AVR_BASIC_TIMER_NORMAL(name,prescaler) \
	enum { name##_freq = cpu_freq/prescaler }; \
	inline void name##_init() \
	{ \
		TCCR0A = 0; \
		TCCR0B = _AVR_TIMER_PRESCALER_BIT(prescaler); \
	} \
	inline uint8_t name##_value() { return TCNT0; }
