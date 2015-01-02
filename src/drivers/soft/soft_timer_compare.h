
#pragma once

#include "soft_timer.h"

#define SOFT_TIMER_COMPARE(name, timer) \
	void name##_init(); \
	void name##_process(); \
	void name##_set_value( timer##_t value ); \
	void name##_irq();

#define IMPLEMENT_SOFT_TIMER_COMPARE(name, timer) \
	static timer##_t _##name##_data = 0; \
	static timer##_t _##name##_timer; \
	void name##_init() \
	{ \
		_##name##_timer = timer##_value(); \
	} \
	void name##_process() \
	{ \
		timer##_t value, timeout, dt; \
		value = timer##_value(); \
		dt = value - _##name##_timer; \
		if( !dt ) return; \
		timeout = _##name##_data - _##name##_timer; \
		_##name##_timer = value; \
		dt %= timer##_period; \
		timeout %= timer##_period; \
		if( dt > timeout ) \
			name##_irq(); \
	} \
	void name##_set_value( timer##_t value ) \
	{ \
		_##name##_data = value; \
		name##_init(); \
	}

