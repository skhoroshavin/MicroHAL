
#include "clock.h"
#include "hal.h"

#include <system/soft_irq.h>

enum
{
	clock_prescale         = clock_timer_freq/clock_freq,
	clock_max_timer_period = (clock_timer_value_t)(-clock_prescale-1)
};

STATIC_ASSERT( clock_freq*clock_prescale == clock_timer_freq, clock );

static clock_timer_value_t _last_timer      = 0;
static clock_timer_value_t _timer_remainder = 0;

static tick_t _clock_value   = 0;
static tick_t _clock_timeout = 0;
static tick_t _last_timeout  = 0;

static tick_t clock_ticks_elapsed()
{
	/* Calculate delta in timer ticks */
	clock_timer_value_t dt, cur_timer;
	cur_timer = clock_timer_value();
	dt = cur_timer - _last_timer;
	dt %= 256;
	_last_timer = cur_timer;

	/* Calculate delta in clock ticks */
	if( clock_prescale == 1 )
	{
		return dt;
	}
	else
	{
		tick_t ticks = dt / clock_prescale;
		_timer_remainder += dt - ticks * clock_prescale;
		if( _timer_remainder >= clock_prescale )
		{
			_timer_remainder -= clock_prescale;
			++ticks;
		}
		return ticks;
	}
}

static void clock_rearm()
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

static uint8_t clock_update()
{
	tick_t ticks = clock_ticks_elapsed();
	_clock_value += ticks;

	if( !_clock_timeout ) return 0;

	if( ticks < _clock_timeout )
	{
		_clock_timeout -= ticks;
		return 1;
	}

	_clock_timeout = clock_timeout( _clock_value - _last_timeout );
	_last_timeout = _clock_value;
	return 1;
}

void clock_compare_irq()
{
	static uint8_t state = 0;
	dbg_write( state );
	state = 1 - state;

	soft_irq_raiseI( clock_soft_irq_id );
}

void clock_init()
{
	clock_timer_start();

	_clock_timeout = clock_timeout( 0 );
	clock_rearm();
}

tick_t clock_value()
{
	return _clock_value;
}

void clock_set_timeout( tick_t timeout )
{
	uint8_t need_rearm = clock_update();

	if( !_clock_timeout || (timeout < _clock_timeout) )
	{
		_clock_timeout = timeout;
		need_rearm = 1;
	}

	if( need_rearm )
		clock_rearm();
}

void clock_soft_irq()
{
	if( clock_update() )
		clock_rearm();
}
