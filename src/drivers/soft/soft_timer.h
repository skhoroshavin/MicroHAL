
#pragma once

#include <drivers/common/timer.h>

#define SOFT_TIMER(name, base, type, prescaler, period) \
	TIMER_COMMON(name, type, base##_freq/prescaler, period) \
	enum { name##_prescaler = prescaler }; \
	name##_t name##_value(); \
	void name##_set_value( name##_t value ); \
	void name##_init(); \
	void name##_process();

#define IMPLEMENT_SOFT_TIMER(name,base) \
	static base##_t _##name##_base_value; \
	static base##_t _##name##_base_remainder; \
	static name##_t _##name##_data = 0; \
	void name##_init() \
	{ \
		_##name##_base_value = base##_value(); \
		_##name##_base_remainder = 0; \
	} \
	void name##_process() \
	{ \
		base##_t dt, value; \
		value = base##_value(); \
		dt = value - _##name##_base_value; \
		if( !dt ) return; \
		dt %= base##_period; \
		_##name##_base_value = value; \
		if( name##_prescaler == 1 ) \
		{ \
			_##name##_data += dt; \
		} \
		else \
		{ \
			name##_t ticks = dt / name##_prescaler; \
			dt -= ticks * name##_prescaler; \
			_##name##_base_remainder += dt; \
			if( _##name##_base_remainder >= name##_prescaler ) \
			{ \
				_##name##_base_remainder -= name##_prescaler; \
				++ticks; \
			} \
			_##name##_data += ticks; \
		} \
		_##name##_data %= name##_period; \
	} \
	name##_t name##_value() \
	{ \
		name##_process(); \
		return _##name##_data; \
	} \
	void name##_set_value( name##_t value ) \
	{ \
		_##name##_data = value; \
		name##_init(); \
	}
