
#include "clock.h"
#include "hal.h"

#include <system/soft_irq.h>

enum
{
	clock_prescale         = clock_timer_freq/clock_freq,
	clock_max_timer_period = (clock_timer_value_t)(-8)
};

STATIC_ASSERT( (uint32_t)clock_freq*clock_prescale == clock_timer_freq, clock );
STATIC_ASSERT( clock_prescale < 254,                                    clock );

static clock_timer_value_t _last_timer      = 0;
static clock_timer_value_t _timer_remainder = 0;

static tick_t _clock_value   = 0;
static tick_t _clock_timeout = 0;
static tick_t _last_timeout  = 0;

static clock_timer_value_t clock_timer_elapsed()
{
	clock_timer_value_t dt, cur_timer;
	cur_timer = clock_timer_value();
	dt = cur_timer - _last_timer;
	dt %= 256;
	_last_timer = cur_timer;

	return dt;
}

static void clock_timer_rearm()
{
	clock_timer_value_t dt, next_timer;

	if( !_clock_timeout )
	{
		clock_compare_irq_disable();
		return;
	}

	if( _clock_timeout > clock_max_timer_period/clock_prescale )
		dt = clock_max_timer_period;
	else
		dt = _clock_timeout * clock_prescale;

	next_timer = _last_timer + dt;
	next_timer %= 256;

	clock_compare_set_value( next_timer );
	clock_compare_irq_enable();
}

static void clock_update( tick_t ticks )
{
	_clock_value += ticks;

	if( _clock_timeout )
	{
		if( ticks < _clock_timeout )
		{
			_clock_timeout -= ticks;
		}
		else
		{
			_clock_timeout = clock_timeout( _clock_value - _last_timeout );
			_last_timeout = _clock_value;
		}

		clock_timer_rearm();
	}
}

void clock_compare_irq()
{
	soft_irq_raiseI( clock_soft_irq_id );
}

void clock_init()
{
	clock_timer_start();

	_clock_timeout = clock_timeout( 0 );
	clock_timer_rearm();
}

tick_t clock_value()
{
	return _clock_value;
}

void clock_set_timeout( tick_t timeout )
{
	clock_soft_irq();

	if( !_clock_timeout || (timeout < _clock_timeout) )
	{
		_clock_timeout = timeout;
		clock_timer_rearm();
	}
}

void clock_soft_irq()
{
	clock_timer_value_t dt = clock_timer_elapsed();
	tick_t ticks = dt;

	if( clock_prescale > 1 )
	{
#if 0
		ticks = dt / clock_prescale;
		dt -= ticks * clock_prescale;
#else
		ticks = 0;
		while( dt >= clock_prescale )
		{
			dt -= clock_prescale;
			++ticks;
		}
#endif
		_timer_remainder += dt;
		if( _timer_remainder >= clock_prescale )
		{
			_timer_remainder -= clock_prescale;
			++ticks;
		}
	}

	clock_update( ticks );
}
