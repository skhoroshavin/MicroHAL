
#pragma once

#define TIMER_COMMON(name,type,freq,period) \
	typedef type name##_t; \
	enum \
	{ \
		name##_freq = freq, \
		name##_period = period \
	};

