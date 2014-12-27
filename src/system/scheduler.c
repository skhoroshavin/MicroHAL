
#include "scheduler.h"
#include <core/interrupts.h>

static struct tasklet_t * volatile _tasklets[TASKLET_QUEUE_COUNT] = { 0, 0, 0 };
static sched_timer_value_t volatile _last_tick;

static void _sched_add( enum tasklet_queue_t tq, struct tasklet_t * tasklet )
{
	tasklet->next = _tasklets[tq];
	_tasklets[tq] = tasklet;
}

static void _sched_process_queue( enum tasklet_queue_t tq, unsigned dt )
{
	struct tasklet_t * tasklet = _tasklets[tq];
	_tasklets[tq] = 0;

	while( tasklet )
	{
		struct tasklet_t * next = tasklet->next;

		if( tasklet->delay > dt )
		{
			tasklet->delay -= dt;
			if( tasklet->delay > sched_latency )
				_sched_add( TASKLET_QUEUE_SHORT, tasklet );
			else
				_sched_add( TASKLET_QUEUE_NOW, tasklet );
		}
		else
			tasklet->func( tasklet->data );

		tasklet = next;
	}
}

void sched_init()
{
	sched_timer_init();
	_last_tick = sched_timer_value();
}

void sched_process()
{
	sched_timer_value_t tick, dt;
	enum tasklet_queue_t tq;

	do
	{
		tick = sched_timer_value();
		dt = tick - _last_tick;
		dt %= sched_period;
		_last_tick = tick;

		for( tq = 0; tq < TASKLET_QUEUE_COUNT; ++tq )
			_sched_process_queue( tq, dt );
	}
	while( _tasklets[TASKLET_QUEUE_NOW] );
}

void sched_tasklet( struct tasklet_t * tasklet, enum tasklet_queue_t tq, unsigned delay )
{
	tasklet->delay = delay;
	_sched_add( tq, tasklet );
}

void sched_delay_ms( struct tasklet_t * tasklet, unsigned ms )
{
	unsigned ticks = ms*sched_timer_freq/1000;
	if( ticks > sched_latency )
		sched_tasklet( tasklet, TASKLET_QUEUE_SHORT, ticks );
	else
		sched_tasklet( tasklet, TASKLET_QUEUE_NOW, ticks );
}
