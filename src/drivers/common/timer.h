
#pragma once

#include <drivers/common/utils.h>

#define TIMER_COMMON(name, type, freq, period, reg, pre_get, post_set) \
	typedef type name##_t; \
	enum \
	{ \
		name##_freq = freq, \
		name##_period = period \
	}; \
	DEFINE_DEVICE_RW(name##_counter, name##_t, reg, pre_get, post_set)

