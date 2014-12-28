
#include "scheduler.h"
#include <core/interrupts.h>

struct tasklet_queue_t
{
	struct tasklet_t * head;
	unsigned           delay;
};

static struct tasklet_queue_t _tasklets[TASKLET_QUEUE_COUNT] =
{
	{ .head = 0, .delay = -1 },
	{ .head = 0, .delay = -1 },
	{ .head = 0, .delay = -1 }
};
static sched_timer_value_t _last_tick;

static void _sched_add( enum tasklet_queue_index_t tq, struct tasklet_t * tasklet )
{
	tasklet->next = _tasklets[tq].head;
	_tasklets[tq].head = tasklet;

	if( tasklet->delay < _tasklets[tq].delay )
		_tasklets[tq].delay = tasklet->delay;
}

static void _sched_process_queue( enum tasklet_queue_index_t tq, unsigned dt )
{
	struct tasklet_t * tasklet = _tasklets[tq].head;
	_tasklets[tq].head = 0;
	_tasklets[tq].delay = -1;

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
	sched_compare_enable();
}

void sched_process()
{
	sched_timer_value_t tick, dt;
	enum tasklet_queue_index_t tq;

	do
	{
		tick = sched_timer_value();
		dt = tick - _last_tick;
		dt %= sched_period;
		_last_tick = tick;

		for( tq = 0; tq < TASKLET_QUEUE_COUNT; ++tq )
			_sched_process_queue( tq, dt );
	}
	while( _tasklets[TASKLET_QUEUE_NOW].head );

	if(_tasklets[TASKLET_QUEUE_SHORT].head )
	{
		sched_timer_value_t next_tick = _last_tick + 24;//_tasklets[TASKLET_QUEUE_SHORT].delay;
		next_tick %= sched_period;
		sched_compare_set_value( next_tick );

		dbg_write( 1 );
		wait_for_irq();
		dbg_write( 0 );

		sched_compare_clear();
	}
}

void sched_tasklet( struct tasklet_t * tasklet, enum tasklet_queue_index_t tq, unsigned delay )
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
