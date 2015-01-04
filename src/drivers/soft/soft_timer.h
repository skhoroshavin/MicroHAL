
#pragma once

#include <drivers/common/timer.h>

/**
 * @brief Software timer definition
 * @param name Timer name
 * @param base Base timer name
 * @param type Timer counter type
 * @param prescaler Timer prescaler
 * @param period Timer period
 */
#define SOFT_TIMER(name, base, type, prescaler, period) \
	extern type _##name##_data; \
	enum { name##_prescaler = prescaler }; \
	void name##_start(); \
	void name##_stop(); \
	void name##_init(); \
	void name##_process(); \
	TIMER_COMMON(name, type, base##_freq/(prescaler), period, _##name##_data, name##_process, name##_init)

/**
 * @brief Software timer implementation
 * @param name Timer name
 * @param base Base timer name
 */
#define IMPLEMENT_SOFT_TIMER(name,base) \
	name##_t _##name##_data = 0; \
	static base##_t _##name##_base_value; \
	static base##_t _##name##_base_remainder; \
	void name##_start() \
	{ \
	 \
	} \
	void name##_stop() \
	{ \
	 \
	} \
	void name##_init() \
	{ \
		_##name##_base_value = base##_counter(); \
		_##name##_base_remainder = 0; \
	} \
	void name##_process() \
	{ \
		base##_t dt, value; \
		value = base##_counter(); \
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
	}
