
#include "clock.h"

#include <system/soft_irq.h>

static tick_t _last_tick;

void clock_compare_irq()
{
	soft_irq_raiseI( clock_soft_irq_id );
}

void clock_init()
{
	_last_tick = clock_timer_value();
	clock_soft_irq();
	clock_timer_start();
}

void clock_set_timeout( tick_t timeout )
{
	if( timeout )
	{
		tick_t next_tick = clock_timer_value() + timeout;
		next_tick %= clock_timer_period;
		clock_compare_set_value( next_tick );
		clock_compare_irq_enable();
	}
	else
	{
		clock_compare_irq_disable();
	}
}

void clock_soft_irq()
{
	tick_t cur_tick, dt;
	cur_tick = clock_timer_value();
	dt = cur_tick - _last_tick;
	dt %= clock_timer_period;
	_last_tick = dt;

	dt = clock_timeout( dt );
	clock_set_timeout( dt );
}
