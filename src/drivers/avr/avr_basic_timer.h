
#pragma once

#include "avr_timer_utils.h"

#define AVR_BASIC_TIMER(name,compa_name,compb_name,prescaler) \
	AVR_TIMER_8(name,0,prescaler) \
	AVR_TIMER_COMP_8(compa_name,0,A) \
	AVR_TIMER_COMP_8(compb_name,0,B)

#define IMPLEMENT_AVR_BASIC_TIMER(name) \
	void name##_init() \
	{ \
		TCCR0A = 0; \
		name##_start(); \
	} \
	ISR(TIMER0_COMPA_vect) { }
