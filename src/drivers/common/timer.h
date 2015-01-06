
#pragma once

#include <drivers/common/utils.h>

#define TIMER_COMMON(name, type, freq, period, reg, update, apply) \
	typedef type name##_t; \
	enum \
	{ \
		name##_freq = freq, \
		name##_period = period \
	}; \
	PROPERTY_REG_RW(name##_counter, name##_t, reg, update, apply)

