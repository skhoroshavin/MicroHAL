
#pragma once

#include "soft_timer.h"

#define SOFT_TIMER_COMPARE(name, timer) \
	timer##_t name##_value(); \
	void name##_set_value( timer##_t value ); \
	void name##_irq_enable(); \
	void name##_irq_disable(); \
	void name##_irq(); \
	void name##_init(); \
	void name##_process();

#define IMPLEMENT_SOFT_TIMER_COMPARE_COMMON(name, timer) \
	static timer##_t _##name##_data = 0; \
	static timer##_t _##name##_timer; \
	timer##_t name##_value() { return _##name##_data; } \
	void name##_set_value( timer##_t value ) \
	{ \
		_##name##_data = value; \
		name##_init(); \
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
	}

#define IMPLEMENT_SOFT_TIMER_COMPARE_POLL(name, timer) \
	IMPLEMENT_SOFT_TIMER_COMPARE_COMMON(name, timer) \
	void name##_irq_enable() \
	{ \
	} \
	void name##_irq_disable() \
	{ \
	} \
	void name##_init() \
	{ \
		_##name##_timer = timer##_value(); \
	} \

#define IMPLEMENT_SOFT_TIMER_COMPARE_IRQ(name, timer, base_timer, base_compare) \
	IMPLEMENT_SOFT_TIMER_COMPARE_COMMON(name, timer) \
	void name##_irq_enable() \
	{ \
		base_compare##_irq_enable(); \
	} \
	void name##_irq_disable() \
	{ \
		base_compare##_irq_disable(); \
	} \
	void name##_init() \
	{ \
		timer##_t timeout; \
		base_timer##_t base_timeout, base_compare; \
		_##name##_timer = timer##_value(); \
		timeout = _##name##_data - _##name##_timer; \
		timeout %= timer##_period; \
		if( timeout * timer##_prescaler < base_timer##_period*3/4 ) \
			base_timeout = timeout * timer##_prescaler; \
		else \
			base_timeout = base_timer##_period*3/4; \
		base_compare = base_timer##_value() + base_timeout; \
		base_compare %= base_timer##_period; \
		base_compare##_set_value( base_compare ); \
	}
