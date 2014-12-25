
#include "scheduler.h"
#include <core/interrupts.h>

enum tasklet_queue_t
{
	TASKLET_QUEUE_IMMEDIATE,
	TASKLET_QUEUE_SHORT,
	TASKLET_QUEUE_LONG,

	TASKLET_QUEUE_COUNT
};

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
				_sched_add( TASKLET_QUEUE_IMMEDIATE, tasklet );
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
	while( _tasklets[TASKLET_QUEUE_IMMEDIATE] );
}

void sched_immediate( struct tasklet_t * tasklet )
{
	_sched_add( TASKLET_QUEUE_IMMEDIATE, tasklet );
}

void sched_short( struct tasklet_t * tasklet, unsigned ticks )
{
	tasklet->delay = ticks;
	_sched_add( TASKLET_QUEUE_SHORT, tasklet );
}

void sched_long( struct tasklet_t * tasklet, unsigned periods )
{
	tasklet->delay = periods;
	_sched_add( TASKLET_QUEUE_LONG, tasklet );
}
