
#pragma once

#define TIMER_COMMON(name,type,reg,freq,period) \
	typedef type name##_t; \
	enum \
	{ \
		name##_freq = freq, \
		name##_period = period \
	}; \
	inline name##_t name##_value() { return reg; } \
	inline void name##_set_value( name##_t value ) { reg = value; }


