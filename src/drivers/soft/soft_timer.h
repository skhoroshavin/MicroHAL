
#pragma once

#include <drivers/common/timer.h>

#define SOFT_TIMER(name, base, type, prescaler) \
	extern type _##name##_data; \
	TIMER_COMMON(name, type, _##name##_data, base##_freq/prescaler, base##_period) \
	inline void name##_start() { base##_start(); } \
	inline void name##_stop()  { base##_stop(); }

#define IMPLEMENT_SOFT_TIMER(name) \
	name##_t _##name##_data;

/*
timer_init()           - initialize timer

Timer compare
compare_value()
compare_set_value()
compare_irq_enable()
compare_irq_disable()
compare_irq()
*/
